package main

import (
	"fmt"
	"time"
)

func producer(sharedValue chan<- int, doneProducer chan<- bool) {

	for i := 0; i < 10; i++ {
		time.Sleep(100 * time.Millisecond)
		fmt.Printf("[producer]: pushing %d\n", i)
		sharedValue <- i
	}
	doneProducer <- true
}

func consumer(sharedValue <-chan int) {

	time.Sleep(1 * time.Second)
	for {
		i := <-sharedValue
		fmt.Printf("[consumer]: %d\n", i)
		time.Sleep(50 * time.Millisecond)
	}

}

func main() {

	sharedValue := make(chan int, 5)
	doneProducer := make(chan bool)

	go consumer(sharedValue)
	go producer(sharedValue, doneProducer)

	<-doneProducer
}
