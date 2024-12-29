package main

import (
	"database/sql"
	"fmt"
	"log"
	"m/db"
	"m/serv"
	"os"

	"github.com/gin-gonic/gin"
	"github.com/go-sql-driver/mysql"
)

type dbCredentials struct {
	user     string
	password string
	addr     string
	dbname   string
}

func connectDatabase(creds dbCredentials) error {

	cfg := mysql.Config{
		User:                 creds.user,
		Passwd:               creds.password,
		Net:                  "tcp",
		Addr:                 creds.addr,
		DBName:               creds.dbname,
		AllowNativePasswords: true,
	}
	var err error
	db.DB, err = sql.Open("mysql", cfg.FormatDSN())
	if err != nil {
		return err
	}
	pingErr := db.DB.Ping()
	if pingErr != nil {
		return pingErr
	}
	return nil
}

const SAME_AS_USER = "(same as username)"

func main() {
	user := os.Getenv("dbuser")
	pwd := os.Getenv("dbpwd")
	err := connectDatabase(dbCredentials{
		user:     user,
		password: pwd,
		addr:     "mysql.agh.edu.pl:3306",
		dbname:   user,
	})
	if err != nil {
		log.Fatal(err)
	}
	fmt.Println("Database Connected.")
	router := gin.Default()

	api := router.Group("api")
	v1 := api.Group("v1")
	{ // initial api thingamabob
		v1.POST("/user", serv.PostUser)
		v1.GET("/user", serv.GetUser)

		v1.GET("/record", serv.GetUserRecord)
		v1.POST("/record", serv.PostUserRecord)
	}

	router.Run("localhost:8080")
	//router.Run("192.168.1.10:80")
	//router.Run("[2a01:116f:a05:f900:4083:8f1a:9d97:efd8]:80")
}
