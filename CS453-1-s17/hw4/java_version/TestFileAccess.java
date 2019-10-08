
/**
 * Test monitor based approach and this is a simple driver program to demonstrate the use of monitor
 * @version 1.0
 * @author xieyi
 * @since 2017-03-09
 *
 */
public class TestFileAccess {
	
	/**
	 * Test driver
	 * user specifies number of threads, max sum (sum = sum(thread id)), iterations is total times to access file for each thread
	 * @param args
	 * @throws InterruptedException
	 */
	public static void main(String args[]) throws InterruptedException {
		if(args.length != 3){
			System.err.println("Usage: java TestFileAccess <numTreads> <max sum> <iterations>");
			System.exit(1);
		}
		
		int numThreads = Integer.parseInt(args[0]);
		int maxSum = Integer.parseInt(args[1]);
		int iterations = Integer.parseInt(args[2]);
		
		//File Access monitor object
		FileAccessMonitor monitor = new FileAccessMonitor(maxSum);
                new Timeout(30);
		for (int i=1; i<= numThreads; i++)
		{
			new FileAccess(i,monitor, iterations).start();
		}
	}
}
