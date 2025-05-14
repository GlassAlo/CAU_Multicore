import java.util.concurrent.atomic.AtomicInteger;

public class ex3 {
    public static void main(String[] args) {
        AtomicInteger atomicInt = new AtomicInteger(0);
        System.out.println("Initial value get(): " + atomicInt.get());

        Thread t2 = new Thread(() -> {
            atomicInt.set(5);
            System.out.println("After set(5): " + atomicInt.get());
        });

        Thread t3 = new Thread(() -> {
            System.out.println("getAndAdd(3) (displays old value): " + atomicInt.getAndAdd(3));
            System.out.println("After getAndAdd: " + atomicInt.get());
        });

        Thread t4 = new Thread(() -> {
            System.out.println("addAndGet(2) (display new value): " + atomicInt.addAndGet(2));
        });

        t2.start();
        t3.start();
        t4.start();

        try {
            t2.join();
            t3.join();
            t4.join();
            System.out.println("Final value: " + atomicInt.get());
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}
