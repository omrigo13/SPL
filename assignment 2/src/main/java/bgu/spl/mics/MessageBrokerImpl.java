package bgu.spl.mics;

import java.util.Iterator;
import java.util.Map;
import java.util.NoSuchElementException;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ConcurrentLinkedQueue;



/**
 * The {@link MessageBrokerImpl class is the implementation of the MessageBroker interface.
 * Write your implementation here!
 * Only private fields and methods can be added to this class.
 */
public class MessageBrokerImpl implements MessageBroker {

	private static MessageBroker instance = null;
	private  Map<Subscriber, ConcurrentLinkedQueue<Message>> subscribersMessages = new ConcurrentHashMap<>();
	private Map<Class<? extends Message>, ConcurrentLinkedQueue<Subscriber>> typesQueue = new ConcurrentHashMap<>();
	private Map<Event<?>, Future> results = new ConcurrentHashMap<>();
	/**
	 * Retrieves the single instance of this class.
	 */

	public static MessageBroker getInstance() {
		//TODO: Implement this
		if (instance == null) {
			instance = new MessageBrokerImpl();

		}
		return instance;
	}

	@Override
	public <T> void subscribeEvent(Class<? extends Event<T>> type, Subscriber m) {
		// TODO Auto-generated method stub
		if(typesQueue!=null)
		{
			typesQueue.computeIfAbsent(type, q->new ConcurrentLinkedQueue<>());
			typesQueue.get(type).add(m);
		}
		}

	@Override
	public void subscribeBroadcast(Class<? extends Broadcast> type, Subscriber m) {
		// TODO Auto-generated method stub
		if(typesQueue!=null)
		{
			typesQueue.computeIfAbsent(type, q->new ConcurrentLinkedQueue<>());
			typesQueue.get(type).add(m);
		}
	}

	@Override
	public synchronized  <T> void complete(Event<T> e, T result) {
			if(results!=null && results.containsKey(e))
			{
				results.get(e).resolve(result);
			}

		}

	@Override
	public  synchronized void sendBroadcast(Broadcast b) {
		// TODO Auto-generated method stub
		if (typesQueue != null && !typesQueue.isEmpty())
		{
			if(typesQueue.containsKey(b.getClass()) && !typesQueue.get(b.getClass()).isEmpty())
			{
				if(subscribersMessages!=null)
				{
					for (Subscriber s : typesQueue.get(b.getClass())) {
						subscribersMessages.get(s).add(b);
					}

				}
			}
		}
		notifyAll();
	}


	@Override
	public  synchronized  <T> Future<T> sendEvent(Event<T> e) {
		// TODO Auto-generated method stub

		if (typesQueue != null && !typesQueue.isEmpty())
		{
			Future future=new Future();
			if(subscribersMessages!=null)
			{
				Subscriber temp = typesQueue.get(e.getClass()).peek();
				if(temp!=null)
				{
					subscribersMessages.get(temp).add(e);
					roundRubbin(typesQueue.get(e.getClass()));
					results.put(e,future);
					notifyAll();
					return future;
				}
				else
					return null;

			}
		}

			return null;
	}


	@Override
	public void register(Subscriber m) {
		// TODO Auto-generated method stub
		subscribersMessages.put(m,new ConcurrentLinkedQueue<>());
	}

	@Override
	public void unregister(Subscriber m) {
		// TODO Auto-generated method stub
			if (subscribersMessages.containsKey(m) == false) {
				throw new NoSuchElementException();
			}
			for (Message message : subscribersMessages.get(m)) {
				subscribersMessages.get(m).remove(message);
				results.get(message).resolve(null);

			}
			subscribersMessages.remove(m);

		Iterator it=typesQueue.entrySet().iterator();
		while(it.hasNext())
		{
			Map.Entry set=(Map.Entry) it.next();
			for(Object s: (ConcurrentLinkedQueue)set.getValue())
			{
				if(s==m)
					((ConcurrentLinkedQueue)set.getValue()).remove(s);
			}
		}

		}

	@Override
	public  Message awaitMessage(Subscriber m) throws InterruptedException {
		// TODO Auto-generated method stub
		if (!subscribersMessages.containsKey(m))
			throw new IllegalStateException("the sub doesnt exist");
			else {
			synchronized (this) {
				try {

					while (subscribersMessages.get(m).isEmpty()) {
						wait();
					}

				} catch (InterruptedException e) {
					Thread.currentThread().interrupt();
					e.printStackTrace();
				}

				return subscribersMessages.get(m).remove();
			}
		}
	}

	public void roundRubbin(ConcurrentLinkedQueue q)
	{

		Subscriber sub= (Subscriber) q.poll();
		if(sub!=null)
			q.add(sub);
	}

}


