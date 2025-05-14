import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.*;

public class ex5 {
    public static void main(String[] args) throws InterruptedException, ExecutionException {
        int range = 200000;
        int numThreads = 4;
        ExecutorService executor = Executors.newFixedThreadPool(numThreads);

        List<Future<Integer>> futures = new ArrayList<>();
        int chunkSize = range / numThreads;

        for (int i = 0; i < numThreads; i++) {
            int start = i * chunkSize + 1;
            int end = (i == numThreads - 1) ? range : start + chunkSize - 1;
            futures.add(executor.submit(new PrimeCounter(start, end)));
        }

        int totalPrimes = 0;
        for (Future<Integer> future : futures) {
            totalPrimes += future.get();
        }

        executor.shutdown();
        System.out.println("Total prime numbers between 1 and " + range + ": " + totalPrimes);
    }

    static class PrimeCounter implements Callable<Integer> {
        private final int start;
        private final int end;

        PrimeCounter(int start, int end) {
            this.start = start;
            this.end = end;
        }

        public Integer call() {
            int count = 0;
            System.out.println("Thread " + Thread.currentThread().getName() + " counting primes from " + start + " to " + end);
            for (int i = start; i <= end; i++) {
                if (isPrime(i)) {
                    count++;
                }
            }
            System.out.println("Thread " + Thread.currentThread().getName() + " found " + count + " primes.");
            return count;
        }

        private boolean isPrime(int num) {
            if (num <= 1) return false;
            for (int i = 2; i <= Math.sqrt(num); i++) {
                if (num % i == 0) return false;
            }
            return true;
        }
    }
}
