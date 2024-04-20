package br.unesp.murilo.Repos;

import java.util.List;

import br.unesp.murilo.Models.MarriageStatus;

public class MarriageStati {
    private List<MarriageStatus> list;

    public MarriageStati() {
    }

    public MarriageStati(List<MarriageStatus> list) {
        this.list = list;
    }

    public List<MarriageStatus> getList() {
        return list;
    }

    public void setList(List<MarriageStatus> list) {
        this.list = list;
    }

    
}
