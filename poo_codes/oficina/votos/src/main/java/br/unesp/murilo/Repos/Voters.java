package br.unesp.murilo.Repos;

import java.util.Date;
import java.util.List;
import java.util.Vector;

import br.unesp.murilo.Models.Address;
import br.unesp.murilo.Models.MarriageStatus;
import br.unesp.murilo.Models.RelationVote;
import br.unesp.murilo.Models.Voter;
import br.unesp.murilo.Models.Work;

public class Voters {
    private List<Voter> list;

    @SuppressWarnings("unused")
    private Voters() {
    }

    public Voters(List<Voter> list) {
        this.list = new Vector<Voter>();
    }

    public void add(String name, Address address, int nChildren, Date birth, MarriageStatus marriageStatus, Work work, float earnings, RelationVote vote){
        this.list.add(new Voter(name, address, nChildren, birth, marriageStatus, work, earnings, vote));
    }

    public List<Voter> getList() {
        return list;
    }

    public void setList(List<Voter> list) {
        this.list = list;
    }

    public void print(){
        System.out.println(list);
    }
    

    
}
