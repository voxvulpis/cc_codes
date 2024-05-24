package br.unesp.murilo.Models;

import java.util.Date;

public class Voter {
    private String name;
    private Address adress;
    private int nChildren;
    private Date birth;
    private MarriageStatus marriageStatus;
    private Work work;
    private float earnings;
    // private Candidate candidate;
    private RelationVote vote;
    
    
    @SuppressWarnings("unused")
    private Voter() {
    }


    public Voter(String name, Address adress, int nChildren, Date birth, MarriageStatus marriageStatus, Work work,
            float earnings, RelationVote vote) {
        this.name = name;
        this.adress = adress;
        this.nChildren = nChildren;
        this.birth = birth;
        this.marriageStatus = marriageStatus;
        this.work = work;
        this.earnings = earnings;
        this.vote = vote;
    }


    public String getName() {
        return name;
    }


    public void setName(String name) {
        this.name = name;
    }


    public Address getAdress() {
        return adress;
    }


    public void setAdress(Address adress) {
        this.adress = adress;
    }


    public int getnChildren() {
        return nChildren;
    }


    public void setnChildren(int nChildren) {
        this.nChildren = nChildren;
    }


    public Date getBirth() {
        return birth;
    }


    public void setBirth(Date birth) {
        this.birth = birth;
    }


    public MarriageStatus getMarriageStatus() {
        return marriageStatus;
    }


    public void setMarriageStatus(MarriageStatus marriageStatus) {
        this.marriageStatus = marriageStatus;
    }


    public Work getWork() {
        return work;
    }


    public void setWork(Work work) {
        this.work = work;
    }


    public float getEarnings() {
        return earnings;
    }


    public void setEarnings(float earnings) {
        this.earnings = earnings;
    }


    public RelationVote getVote() {
        return vote;
    }


    public void setVote(RelationVote vote) {
        this.vote = vote;
    }


    // public Candidate getCandidate() {
    //     return candidate;
    // }


    // public void setCandidate(Candidate candidate) {
    //     this.candidate = candidate;
    // }

    
    
}
