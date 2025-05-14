import java.util.concurrent.locks.ReentrantReadWriteLock;

public class ex2 {
    private static final ReentrantReadWriteLock rwLock = new ReentrantReadWriteLock();
    private static int value = 0;

    public static void main(String[] args) {
        Thread writer = new Thread(() -> {
            System.out.println("Writer waiting to lock write...");
            rwLock.writeLock().lock();
            System.out.println("Writer acquired lock write.");
            for (int i = 0; i < 5; i++) {
                try {
                    value = 42 * (i + 1);
                    Thread.sleep(1000); // Simulate some processing time
                    System.out.println("Writer updated value to " + value);
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                }
            }
            rwLock.writeLock().unlock();
            System.out.println("Writer released lock write.");
        });

        Thread reader = new Thread(() -> {
            System.out.println("Reader waiting to lock read only...");
            rwLock.readLock().lock();
            System.out.println("Reader acquired lock read only.");
            try {
                System.out.println("Reader read value: " + value);
            } finally {
                rwLock.readLock().unlock();
            }
        });

        Thread reader2 = new Thread(() -> {
            System.out.println("Reader2 waiting to lock read only...");
            rwLock.readLock().lock();
            System.out.println("Reader2 acquired lock read only.");
            try {
                System.out.println("Reader2 read value: " + value);
            } finally {
                rwLock.readLock().unlock();
            }
        });

        writer.start();
        reader.start();
        reader2.start();

        try {
            writer.join();
            reader.join();
            reader2.join();
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }
}
