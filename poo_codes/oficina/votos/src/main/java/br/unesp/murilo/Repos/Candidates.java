package br.unesp.murilo.Repos;

import java.util.List;

import br.unesp.murilo.Models.Candidate;

public class Candidates {
    private List<Candidate> list;

    public Candidates() {
    }

    public Candidates(List<Candidate> list) {
        this.list = list;
    }

    public List<Candidate> getList() {
        return list;
    }

    public void setList(List<Candidate> list) {
        this.list = list;
    }

    public void print(){
        System.out.println(this.list);
    }
}
