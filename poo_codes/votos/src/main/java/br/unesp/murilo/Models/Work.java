package br.unesp.murilo.Models;

public class Work {
    private String Type;

    @SuppressWarnings("unused")
    private Work() {
    }

    public Work(String type) {
        Type = type;
    }

    public String getType() {
        return Type;
    }

    public void setType(String type) {
        Type = type;
    }

    
}
