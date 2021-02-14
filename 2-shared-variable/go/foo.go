package main

import (
	"fmt"
	"runtime"
)

func numberServer(add <-chan int, sub <-chan int, read chan<- int) {
	var number = 0

	for {
		select {
		case <-add:
			number++
		case <-sub:
			number--
		case read <- number:

		}
	}
}

func incrementer(add chan<- int, finished chan<- bool) {
	for j := 0; j < 1000000; j++ {
		add <- 1
	}
	finished <- true
}

func decrementer(sub chan<- int, finished chan<- bool) {
	for j := 0; j < 1000000+1; j++ {
		sub <- 1
	}
	finished <- true
}

func main() {
	runtime.GOMAXPROCS(runtime.NumCPU())

	read := make(chan int)
	add := make(chan int)
	sub := make(chan int)
	finishedAdd := make(chan bool)
	finishedSub := make(chan bool)

	go numberServer(add, sub, read)
	go incrementer(add, finishedAdd)
	go incrementer(sub, finishedSub)

	<-finishedAdd
	<-finishedSub

	fmt.Println("The magic number is:", <-read)
}
