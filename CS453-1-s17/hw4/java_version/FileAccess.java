import java.util.Random;

/**
 * File Access thread
 * @author xieyi
 *
 */
public class FileAccess extends Thread{

	private int id; 	//thread id
	private int iterations;		//how many times each thread id could access the file
	FileAccessMonitor flMonitor; //file access monitor
	private int min = 1000; //minimum random seconds 
	private int max = 4000;	//maximum random seconds
	
	
	/**
	 * FileAccess object constructor
	 * @param id thread id
	 * @param flMonitor	file access monitor
	 * @param iterations	file access times
	 */
	public FileAccess (int id, FileAccessMonitor flMonitor, int iterations){
		this.flMonitor = flMonitor;
		this.id = id;
		this.iterations = iterations;
	}
	
	/* (non-Javadoc)
	 * @see java.lang.Thread#run()
	 */
	@Override
	public void run(){

		for(int i = 1; i <= iterations; i++)
		{
			System.out.println("Thread "+id+" starting up.");
			flMonitor.startAccess(id);
			try {
				sleep(randInt(min, max));
			}catch (InterruptedException ex){
				System.err.println(ex);;
			}
			flMonitor.endAccess(id);
			try {
				sleep(randInt(min, max));
			}catch (InterruptedException ex){
				System.err.println(ex);;
			}
		}
	}
	
	private int randInt(int min, int max){
		Random rnd;
		rnd = new Random();
		return rnd.nextInt(max-min)+min;
	}
	
}
