package db

import (
	"database/sql"
	"fmt"
)

type User struct {
	ID       uint64 `json:"uid"`      // id użytkownika
	Username string `json:"username"` // nazwa użytkownika
}

type GameLevel struct {
	Chapter uint8 `json:"chapter"` // epizod
	Level   uint8 `json:"level"`   // poziom
}

type UserRecordID struct {
	ID     uint64    `json:"uid"`    // id użytkownika
	Time   float64   `json:"time"`   // czas w którym zakończono
	Points uint32    `json:"points"` // punkty
	Level  GameLevel `json:"level"`  // poziom
}

type UserRecordUname struct {
	Username string    `json:"username"` // nazwa użytkownika
	Time     float64   `json:"time"`     // czas w którym zakończono
	Points   uint32    `json:"points"`   // punkty
	Level    GameLevel `json:"level"`    // poziom
}

type UserRecordOptions struct {
	SearchBy   string    `json:"search-by"`   // "level", "username", "time", "points"
	NumRecords uint8     `json:"num-records"` // 1-255
	Level      GameLevel `json:"level"`       // poziom
	Username   string    `json:"username"`    // nazwa użytkownika
	Time       float64   `json:"time"`        // czas
	Points     uint32    `json:"points"`      // punkty
	Condition  string    `json:"condition"`   // "<", "<=", "=", ">", ">=", czas i punkty
}

var DB *sql.DB

func AddUser(uname string) (int64, error) {
	result, err := DB.Exec("INSERT INTO user (username) VALUES (?)", uname)
	if err != nil {
		return 0, fmt.Errorf("AddUser: %v", err)
	}
	id, err := result.LastInsertId()
	if err != nil {
		return 0, fmt.Errorf("AddUser: %v", err)
	}
	return id, nil
}

func AddRecord(rec UserRecordID) (UserRecordID, error) {
	result, err := DB.Exec(
		"INSERT INTO userRecord (uid, time, points, chapter, level)"+
			"VALUES (?, ?, ?, ?, ?)",
		rec.ID, rec.Time, rec.Points, rec.Level.Chapter, rec.Level.Level)
	if err != nil {
		return UserRecordID{}, fmt.Errorf("AddRecord: %v", err)
	}
	fmt.Printf("result: %v\n", result)
	return rec, nil
}

func UserByName(uname string) (User, error) {
	var user User
	row := DB.QueryRow("SELECT * FROM user WHERE username = ?", uname)
	if err := row.Scan(&user.ID, &user.Username); err != nil {
		if err == sql.ErrNoRows {
			return user, fmt.Errorf("userByName %q: no such user", uname)
		}
		return user, fmt.Errorf("userByName %q: %v", uname, err)
	}
	return user, nil
}

func RecordsByUser(options UserRecordOptions) ([]UserRecordUname, error) {
	var records []UserRecordUname
	if options.NumRecords < 1 {
		options.NumRecords = 1
	}
	rows, err := DB.Query(
		"SELECT * FROM userRecord R INNER JOIN user U ON R.uid = U.uid WHERE username = ? "+
			"LIMIT ?",
		options.Username, options.NumRecords)
	if err != nil {
		return nil, fmt.Errorf("RecordsByUser1 %v: %v", options, err)
	}
	for rows.Next() {
		var rec UserRecordUname
		var yeet uint64
		if err := rows.Scan(&yeet, &rec.Time, &rec.Points, &rec.Level.Chapter, &rec.Level.Level, &yeet, &rec.Username); err != nil {
			return nil, fmt.Errorf("RecordsByUser2 %v: %v", options, err)
		}
		records = append(records, rec)
	}
	if err := rows.Err(); err != nil {
		return nil, fmt.Errorf("RecordsByUser3 %v: %v", options, err)
	}
	return records, nil
}
