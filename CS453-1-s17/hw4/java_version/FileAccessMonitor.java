import java.util.Timer;
import java.util.TimerTask;
/**
 * File access monitor
 * @author xieyi
 *
 */
public class FileAccessMonitor extends TimerTask{
	private int maxSum;
	private int sum = 0;
        private Timer timer;

	
	/**
	 * Constructor 
	 */
	public FileAccessMonitor(){
	}
	
	
	/**
	 * Constructor
	 * @param maxSum max sum of thread id number
	 */
	public FileAccessMonitor(int maxSum){
		this.maxSum = maxSum;
                this.timer = new Timer(true);
                timer.scheduleAtFixedRate(this,30000,1000); //every second after 30 seconds
	}
	
	/**
	 * Synchronized file startAccess
	 * @param id thread id number
	 */
	public synchronized void startAccess(int id) {
		sum = sum + id;
		System.out.println("Thread " + id + " starting file access.");
		while (sum > maxSum){
			try {
				this.wait(); 
				
			} catch(InterruptedException ex){
				System.err.println(ex);
			}
		}
		this.notify();
	}
	
	/**
	 * Synchronized file end Access
	 * @param id
	 */
	public synchronized void endAccess(int id){
		sum -= id;
		this.notify();
		System.out.println("Thread " + id + " ending file access.");
	}

        @Override
        public void run(){
	    System.out.println("Aieeeeee...received an alarm. Timeout!");
	    System.exit(1);
        }

}
