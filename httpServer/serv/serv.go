package serv

import (
	"log"
	"m/db"
	"net/http"

	"github.com/gin-gonic/gin"
)

func PostUser(c *gin.Context) {
	var nuser db.User
	if err := c.BindJSON(&nuser); err != nil {
		log.Print(err)
		return
	}
	lastInsert, err := db.AddUser(nuser.Username)
	if err != nil {
		c.IndentedJSON(http.StatusInternalServerError, err.Error())
	} else {
		nuser.ID = uint64(lastInsert)
		c.IndentedJSON(http.StatusCreated, nuser)
	}
}

func PostUserRecord(c *gin.Context) {
	var recnamed db.UserRecordUname
	if err := c.BindJSON(&recnamed); err != nil {
		log.Print(err)
		return
	}
	user, err := db.UserByName(recnamed.Username)
	if err != nil {
		c.IndentedJSON(http.StatusInternalServerError, err.Error())
	}
	var rec db.UserRecordID
	rec.ID = user.ID
	rec.Time = recnamed.Time
	rec.Points = recnamed.Points
	rec.Level = recnamed.Level

	rec, err = db.AddRecord(rec)
	if err != nil {
		c.IndentedJSON(http.StatusInternalServerError, err.Error())
	}
	c.IndentedJSON(http.StatusCreated, rec)
}

func GetUser(c *gin.Context) {
	var nuser db.User
	if err := c.BindJSON(&nuser); err != nil {
		log.Print(err)
		return
	}
	user, err := db.UserByName(nuser.Username)
	if err != nil {
		c.IndentedJSON(http.StatusNotFound, err.Error())
	} else {
		c.IndentedJSON(http.StatusFound, user)
	}
}

func GetUserRecord(c *gin.Context) {
	var options db.UserRecordOptions
	if err := c.BindJSON(&options); err != nil {
		log.Print(err)
		return
	}
	if options.SearchBy == "username" {
		rec, err := db.RecordsByUser(options)
		if err != nil {
			c.IndentedJSON(http.StatusNotFound, err.Error())
		}
		c.IndentedJSON(http.StatusFound, rec)
	} else {
		c.IndentedJSON(http.StatusBadRequest, options)
	}
}
