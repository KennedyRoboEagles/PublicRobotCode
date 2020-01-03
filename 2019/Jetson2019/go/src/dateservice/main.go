package main

import (
	"bytes"
	"encoding/json"
	"fmt"
	"net/http"
	"os/exec"
	"strings"
	"time"

	"github.com/spf13/pflag"

	"github.com/gorilla/mux"
	log "github.com/sirupsen/logrus"
	"golang.org/x/crypto/ssh"
)

type DateResponse struct {
	DSSynced bool
	Time     time.Time
}

type RoboRio struct {
	hostname string
	port     int
	config   *ssh.ClientConfig
}

var systemTimeSet = false

func (r *RoboRio) execute(command string) (string, error) {
	conn, err := ssh.Dial("tcp", fmt.Sprintf("%s:%d", r.hostname, r.port), r.config)
	if err != nil {
		return "", err
	}
	session, err := conn.NewSession()
	if err != nil {
		return "", err
	}
	defer session.Close()

	// RUn the command
	var stdoutBuf bytes.Buffer
	session.Stdout = &stdoutBuf
	session.Run(command)

	log.Info(fmt.Sprintf("%s -> %s", r.hostname, stdoutBuf.String()))

	return stdoutBuf.String(), nil
}

func (r *RoboRio) getTime() (time.Time, error) {
	rioTimeStr, err := r.execute("date --utc")
	if err != nil {
		return time.Time{}, err
	}
	rioTimeStr = strings.TrimRight(rioTimeStr, " \n")

	log.Info("Time String: ", rioTimeStr)
	// const rfc2822 = "Mon, 02 Jan 2006 15:04:05 -0700"
	rioTime, err := time.Parse(time.UnixDate, rioTimeStr)
	if err != nil {
		return time.Time{}, err
	}
	log.Info("Time: ", rioTime)

	return rioTime, nil
}

var enableSystemTimeSet = false

func main() {
	setSystemTimeArg := pflag.Bool("set", false, "Set system time")
	pflag.Parse()
	enableSystemTimeSet = *setSystemTimeArg

	log.Info("Set system time: ", setSystemTime)

	r := mux.NewRouter()
	r.Use(loggingMiddleware)

	rio := &RoboRio{
		hostname: "roborio-3081-frc.local",
		port:     22,
	}
	rio.config = &ssh.ClientConfig{
		User: "lvuser",
		Auth: []ssh.AuthMethod{
			ssh.Password(""),
		},
		HostKeyCallback: ssh.InsecureIgnoreHostKey(),
		Timeout:         5 * time.Second,
	}

	r.HandleFunc("/date", func(w http.ResponseWriter, r *http.Request) {
		dateHandler(w, r, rio)
	})

	go runPeriodic(rio)

	log.Info("Listening on :5810...")
	http.Handle("/", r)
	http.ListenAndServe(":5810", nil)

}

func loggingMiddleware(next http.Handler) http.Handler {
	return http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
		// Do stuff here
		log.Info("Request on: ", r.RequestURI)
		// Call the next handler, which can be another middleware in the chain, or the final handler.
		next.ServeHTTP(w, r)
	})
}

func dateHandler(w http.ResponseWriter, r *http.Request, rio *RoboRio) {
	rioTime, err := rio.getTime()
	if err != nil {
		panic(err)
	}

	// Send response
	response := DateResponse{
		Time:     rioTime,
		DSSynced: isDSSynced(rioTime),
	}
	body, err := json.MarshalIndent(response, "", "  ")
	if err != nil {
		panic(err)
	}

	w.Write(body)
}

func isDSSynced(rioTime time.Time) bool {
	cutOffDate, err := time.Parse(time.RFC3339, "2018-02-28T00:00:00Z")
	if err != nil {
		panic(err)
	}

	return rioTime.After(cutOffDate)
}

func runPeriodic(rio *RoboRio) {
	ticker := time.NewTicker(2 * time.Second)

	for {
		select {
		case <-ticker.C:
			periodic(rio)
		}
	}
}

func setSystemTime(t time.Time) error {
	systemTimeSet = true

	formatStr := t.Format(time.UnixDate)

	log.Info("Setting system time to: ", formatStr)
	if enableSystemTimeSet {
		dateCmd := fmt.Sprintf(`sudo date -s "%s"`, formatStr)
		log.Info("Executing command: ", dateCmd)
		err := exec.Command("/bin/bash", "-c", dateCmd).Run()
		if err != nil {
			return err
		}
	}

	return nil
}

func periodic(rio *RoboRio) {
	defer func() {
		if r := recover(); r != nil {
			fmt.Println("Error:", r)
		}
	}()

	if systemTimeSet {
		return
	}

	log.Info("Requesting rio time")
	rioTime, err := rio.getTime()
	if err != nil {
		panic(err)
	}

	if isDSSynced(rioTime) {
		err := setSystemTime(rioTime)
		if err != nil {
			panic(err)
		}
	}

}
