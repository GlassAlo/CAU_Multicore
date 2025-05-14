import java.util.concurrent.Semaphore;

class ParkingGarage {
    private final Semaphore semaphore;

    public ParkingGarage(int places) {
        if (places < 0) {
            places = 0;
        }
        this.semaphore = new Semaphore(places, true); // fair semaphore
    }

    public void enter(String carName) {
        try {
            System.out.println(carName + ": trying to enter");
            semaphore.acquire(); // block if no permits available
            System.out.println(carName + ": just entered");
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }

    public void leave(String carName) {
        System.out.println(carName + ":                 about to leave");
        semaphore.release(); // release a permit (i.e., leave the parking garage)
        System.out.println(carName + ":                 have been left");
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
                Thread.sleep((int)(Math.random() * 10000)); // simulate driving
                parkingGarage.enter(getName());
                Thread.sleep((int)(Math.random() * 20000)); // simulate parking duration
                parkingGarage.leave(getName());
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }
    }
}

public class ParkingSemaphore {
    public static void main(String[] args) {
        ParkingGarage garage = new ParkingGarage(7); // 7 parking places
        for (int i = 1; i <= 10; i++) {
            new Car("Car " + i, garage);
        }
    }
}
