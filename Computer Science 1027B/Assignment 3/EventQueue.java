/**
 * @author Jameel Kaba
 * CS1027B Assignment 3
 * This class represents a queue of events 
 * with methods to insert and delete the events
 */
public class EventQueue {
	final int impossibleNumItemsValue=-1;

	QueueADT<Event> eventQueue;

	// Constructor

	/**
	 * Constructor that creates a new EventQueue object
	 */

	public EventQueue() {
		eventQueue=new LinkedQueue<Event>();
	}

	/////////////////////////////////////////////////////////////////
	// Insert events one at a time in sorted order on eventTime
	/////////////////////////////////////////////////////////////////

	/**
	 * insertEvent method that inserts Event into 
	 * an EventQueue one by one organizing the events based on time
	 * @param insertEvent the event that is going to be inserted
	 * @param debug if true then debug printing occurs
	 */

	public void insertEvent(Event insertEvent,boolean debug) {
		String s;

		// Debug printing
		if(debug)
		{
			System.out.format("\nINSERT EVENT:\nEvent time: %7.2f Event type: %s",
					insertEvent.getEventTime(),insertEvent.getEventType());
			if(insertEvent.getEventNumItems()!=impossibleNumItemsValue)
				System.out.format(" Event number of items: %d",insertEvent.getEventNumItems());
			System.out.format("\n");
		}

		// Debug printing
		if(debug)
		{
			System.out.println("\nEvent Queue before new event enqueued");
			System.out.println("-------------------------------------");
			s=eventQueue.toString();

			if(!s.equals(""))
				System.out.println(s);
			else
				System.out.println("Empty Queue");

			System.out.println("\n");
		}


		// Insert your code here to do the insertion

		/**
		 * The following is the process for how the code works
		 * Creates a new linked queue of generic type event called temp
		 * enqueue the new event into the eventQueue
		 * while the eventQueue is not empty
		 * events are dequeued from eventQueue
		 * and then enqueued in temp
		 * goes through a series of checks to ensure that the events are placed in order
		 * once the events are in order make eventQueue copy the contents of temp
		 */

		// Creates a new LinkedQueue object of type Event called temp
		LinkedQueue<Event> temp = new LinkedQueue<Event>();

		// Enqueue the new event into eventQueue
		// this is to ensure that the program will go through 
		// the while loop to organize the events
		eventQueue.enqueue(insertEvent);

		// While the eventQueue is not empty
		while(!eventQueue.isEmpty()){

			// Create a new event object called event1
			// that refers to the object
			// that is dequeued from the eventQueue
			Event event1 = eventQueue.dequeue();

			/**
			 * The following code is a series of checks 
			 * to ensure that the events are placed in the 
			 * correct order based on time
			 */

			// If the new event takes less time than event1
			if(insertEvent.getEventTime() < event1.getEventTime()){

				// We enqueue the new event into temp
				// followed by event1
				temp.enqueue(insertEvent);

				temp.enqueue(event1);

				// We create a new event object event2 
				// that refers to the next object that is in
				// the eventQueue
				Event event2 = eventQueue.dequeue();

				// If the new event is not the same event as event2
				// enqueue event2 in temp
				if(!insertEvent.equals(event2)){

					temp.enqueue(event2);

					// While the eventQueue is not empty
					while(!eventQueue.isEmpty()){

						// We create another new event object event3
						// that refers to the next object in the eventQueue
						Event event3 = eventQueue.dequeue();

						// If the new event is not the same event as event3
						// enqueue event3 into temp
						if(!insertEvent.equals(event3)){

							temp.enqueue(event3);

						}						
					}
				}
			}

			// Else if the new event takes more time than event1
			// check to see if eventQueue is not empty
			else if(!eventQueue.isEmpty()){

				// We enqueue event1 into temp
				temp.enqueue(event1);

				// While the eventQueue is not empty
				while(!eventQueue.isEmpty()){

					// We create a new event object event2
					// that refers to the object that is dequeued from eventQueue
					Event event2 = eventQueue.dequeue();

					// If the new event takes more time than event2
					// enqueue event2
					if(insertEvent.getEventTime() > event2.getEventTime()){

						temp.enqueue(event2);
						
					}

					// Otherwise we enqueue the new event 
					else{

						temp.enqueue(insertEvent);

						// If the new event and event2 are not the same event
						// we enqueue event2 into temp
						if(!insertEvent.equals(event2)){

							temp.enqueue(event2);
							
						}

						// While the eventQueue is not empty
						while(!eventQueue.isEmpty()){

							// We create a new event object event3
							// that refers to the object that is dequeued from eventQueue
							Event event3 = eventQueue.dequeue();

							// If the new event and event3 are not the same
							if(!insertEvent.equals(event3)){

								temp.enqueue(event3);

							}
						}
					}
				}
			}

			// Else if both the new event takes more time than event1
			// and eventQueue is empty
			// we enqueue event1 into temp
			else{
				
				temp.enqueue(event1);
				
			}
		}	

		// Once the loop exits we make
		// the empty eventQueue copy the contents from temp
		eventQueue = temp;

		// Debug printing
		if(debug)
		{
			System.out.println("\nEvent Queue after new event enqueued");
			System.out.println("------------------------------------");
			s=eventQueue.toString();

			if(!s.equals(""))
				System.out.println(s);
			else
				System.out.println("Empty Queue");

			System.out.println("\n");
		}

	}

	/////////////////////////////////////////////////////////////////////////
	// Delete all events from order queue whose eventTime >= minAllDoneTime
	/////////////////////////////////////////////////////////////////////////

	/**
	 * deleteEvent method that deletes events from the EventQueue
	 * if the event time is more than the minAllDoneTime
	 * @param minAllDoneTime the lowest event time for an Event of type ALL_DONE
	 * @param debug if true debug printing occurs
	 */

	public void deleteEvents(double minAllDoneTime,boolean debug) {
		// this method assumes that the queue is already sorted
		// We dequeue events from eventQueue until the eventTime >= minAllDoneTime
		// and enqueue them in backwards order in tempQueue.
		// The first ALL_DONE event whose eventTime is
		// equal to minAllDoneTime is enqueued in tempQueue as well.
		// The eventQueue is then emptied and lastly tempQueue is copied back into
		// now empty eventQueue in correct sorted order.

		String s;

		// Debug printing
		if(debug)
		{
			System.out.println("\nEvent Queue before all events with eventTime >" + 
					minAllDoneTime + " deleted");
			System.out.println("------------------------------------------------------");
			s=eventQueue.toString();

			if(!s.equals(""))
				System.out.println(s);
			else
				System.out.println("Empty Queue");

			System.out.println("\n");
		}

		// Insert your code here to do the deletion

		/**
		 * The following is the process as to how the code works
		 * we create a new LinkedQueue of type event called temp
		 * while the eventQueue is not empty
		 * we compare the time between the events
		 * if an event of type ALL_DONE is found
		 * we proceed to empty out eventQueue 
		 * if an event of type ALL_DONE is not found
		 * a warning message is printed
		 * once eventQueue is empty we make it copy the contents of temp
		 */

		// Create a new LinkedQueue of type event called temp
		LinkedQueue<Event> temp = new LinkedQueue<Event>();

		// While the eventQueue is not empty
		while(!eventQueue.isEmpty()){

			// We create an event object event1
			// that refers to the object that is dequeued 
			// by the eventQueue
			Event event1 = eventQueue.dequeue();

			// If event1 takes less than or the same amount of time
			// as the minAllDoneTime
			// we enqueue event1 into temp
			if(event1.getEventTime() <= minAllDoneTime){

				temp.enqueue(event1);

				// If event1 is of type ALL_DONE
				// we proceed to empty out the queue
				// this is to ensure that there is only one element of 
				// type ALL_DONE
				if(event1.getEventType().equals("ALL_DONE")){

					while(!eventQueue.isEmpty()){

						eventQueue.dequeue();
						
					}
				}

				// If event1 is never of type ALL_DONE each time it goes through the loop
				// print out a warning message saying that there are no events of type ALL_DONE
				else if(!event1.getEventType().equals("ALL_DONE")){

					if(eventQueue.isEmpty()){

						System.out.println("WARNING: There are no events that are of type ALL_DONE");
						
					}
				}
			}
		}

		// Once the loop is exited
		// we make the empty eventQueue copy the 
		// contents from temp
		eventQueue = temp;

		// Debug printing
		if(debug)
		{
			System.out.println("\nEvent Queue after all events with eventTime >" + 
					minAllDoneTime + " deleted");
			System.out.println("-----------------------------------------------------");
			s=eventQueue.toString();

			if(!s.equals(""))
				System.out.println(s);
			else
				System.out.println("Empty Queue");

			System.out.println("\n");
		}

	}

}
