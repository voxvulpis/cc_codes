package br.unesp.murilo.Models;

public class Car extends Vehicle {
    private int passegers;

    public Car() {
    }

    public Car(int passegers, String name) {
        super(name);
        this.passegers = passegers;
    }

    public int getPassegers() {
        return passegers;
    }

    public void setPassegers(int passegers) {
        this.passegers = passegers;
    }

    
}
