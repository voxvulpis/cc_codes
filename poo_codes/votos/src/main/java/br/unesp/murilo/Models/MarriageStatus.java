package br.unesp.murilo.Models;

public class MarriageStatus {
    private String status;


    @SuppressWarnings("unused")
    private MarriageStatus() {
    }

    public MarriageStatus(String status) {
        this.status = status;
    }

    public String getStatus() {
        return status;
    }

    public void setStatus(String status) {
        this.status = status;
    }

    
}
