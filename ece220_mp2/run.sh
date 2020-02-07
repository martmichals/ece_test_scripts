#!/usr/bin/expect
spawn lc3as prog2.asm
spawn lc3sim
set timeout -1

expect "(lc3sim)"
send -- "file prog2\r"

expect "*(lc3sim)"
send -- "continue\r"

expect ">"
set foo [ lindex $argv 0 ]
set timeout 1
send -- $foo

expect "(lc3sim)"
send -- "quit\n"


interact

