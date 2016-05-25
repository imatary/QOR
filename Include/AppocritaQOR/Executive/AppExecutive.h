//AppExecutive.h

//responsible for creating command queues and processing them

//Consider how to manage queue priorities:

//process each queue in linear order but only do a decrement of its counter from max value. Only actually process the queue when the value reaches 0
//Reset the value to max after processing

//In this way a 1 in N share in approximated

//Priority values 1 - 1000 so we can have 1 in 1 to 1 in 1000 processing

//Queues can up their priority by cutting the max for the next reset. In this way users can prioritise one task over another even on a single thread.

//As the list of queues is processed the lowest current queue value should be determined and this then used as the threshold on the next pass so we don't waste cyles counting down repeatedly from
//1000 when we've only got a low priority queue

//Probably do this by keeping the index sorted, reinserting newly reset counters lower down the list


