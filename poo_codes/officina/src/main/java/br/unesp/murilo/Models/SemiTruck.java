package br.unesp.murilo.Models;

public class SemiTruck extends Vehicle {
    private int axis;

    public SemiTruck() {
    }

    public SemiTruck(int axis, String name) {
        super(name);
        this.axis = axis;
    }

    public int getAxis() {
        return axis;
    }

    public void setAxis(int axis) {
        this.axis = axis;
    }

    
}
