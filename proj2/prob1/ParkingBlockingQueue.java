import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.BlockingQueue;

class ParkingGarage {
    private final BlockingQueue<Integer> parkingSlots;

    public ParkingGarage(int capacity) {
        if (capacity < 0) {
            capacity = 0;
        }
        parkingSlots = new ArrayBlockingQueue<>(capacity);
    }

    public void enter(String carName) {
        try {
            System.out.println(carName + ": trying to enter");
            parkingSlots.put(1);
            System.out.println(carName + ": just entered");
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }

    public void leave(String carName) {
        try {
            System.out.println(carName + ":                 about to leave");
            parkingSlots.take();
            System.out.println(carName + ":                 have been left");
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }
}

class Car extends Thread {
    private final ParkingGarage parkingGarage;

    public Car(String name, ParkingGarage garage) {
        super(name);
        this.parkingGarage = garage;
        start();
    }

    @Override
    public void run() {
        while (true) {
            try {
                Thread.sleep((int) (Math.random() * 10000)); // simulate driving before parking
                parkingGarage.enter(getName());
                Thread.sleep((int) (Math.random() * 20000)); // simulate time spent parked
                parkingGarage.leave(getName());
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }
    }
}

public class ParkingBlockingQueue {
    public static void main(String[] args) {
        ParkingGarage parkingGarage = new ParkingGarage(7);
        for (int i = 1; i <= 10; i++) {
            new Car("Car " + i, parkingGarage);
        }
    }
}
