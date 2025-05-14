import java.util.concurrent.BrokenBarrierException;
import java.util.concurrent.CyclicBarrier;

public class ex4 {
    public static void main(String[] args) {
        int parties = 3;
        CyclicBarrier barrier = new CyclicBarrier(parties, () -> {
            System.out.println("All parties have arrived at the barrier, let's proceed.");
        });

        for (int i = 0; i < parties; i++) {
            new Thread(new Task(barrier)).start();
        }
    }

    static class Task implements Runnable {
        private final CyclicBarrier barrier;

        Task(CyclicBarrier barrier) {
            this.barrier = barrier;
        }

        public void run() {
            try {
                System.out.println(Thread.currentThread().getName() + " is waiting at the barrier.");
                barrier.await();
                System.out.println(Thread.currentThread().getName() + " has crossed the barrier.");
            } catch (InterruptedException | BrokenBarrierException e) {
                e.printStackTrace();
            }
        }
    }
}
