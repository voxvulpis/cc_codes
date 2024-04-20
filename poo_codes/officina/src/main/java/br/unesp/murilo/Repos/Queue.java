package br.unesp.murilo.Repos;

import java.util.List;
import java.util.Vector;

import br.unesp.murilo.Models.Car;
import br.unesp.murilo.Models.SemiTruck;
import br.unesp.murilo.Models.Vehicle;

public class Queue {
    private List<Vehicle> vehicles;

    // public Queue(Vehicle vehicle) {
    //     vehicles.add(vehicle);
    // }

    public Queue() {
        vehicles = new Vector<Vehicle>() ;
    }

    public List<Vehicle> getVehicles() {
        return vehicles;
    }

    // public void setVehicles(List<Vehicle> vehicles) {
    //     this.vehicles = vehicles;
    // }

    public void add(Vehicle vehicle){
        vehicles.add(vehicle);
        System.out.println("\n[ADDED NEW VEHICLE TO END OF QUEUE]\n");
    }

    public void popOff(){
        System.out.println("\n[POP VEHICLE]" + vehicles.get(0).getName() + "\n");
        vehicles.remove(0);
    }

    public String toString(){
        String str = new String();
        int i = 0;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
        str += "Queue of vehicles: \n\t";

        if(vehicles.isEmpty()){
            str += "[Empty]";
        }
        else for (Vehicle vehicle : vehicles) {

            // str += "\n\t" + i + ":\t" + vehicle.getName();
            
            str += "\n" + i + "\tName: \t" + vehicle.getName();

            if (vehicle.getClass() == Car.class) {
                Car car = (Car)vehicle;
                str += "\n\tPass.: \t" + car.getPassegers();
            }
            else{
                SemiTruck semiTruck = (SemiTruck)vehicle;
                str += "\n\tAxis: \t" + semiTruck.getAxis();
            }
            i++;
            str += "\n";

            
        }

        str += "\n";
        

        return str;
    }

    
    
}
