package br.unesp.murilo.Models;

public class Address {
    // TODO
    private String address;

    @SuppressWarnings("unused")
    private Address() {
    }

    public Address(String address) {
        this.address = address;
    }

    public String getAddress() {
        return address;
    }

    public void setAddress(String address) {
        this.address = address;
    }

    
}
