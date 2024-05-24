package br.unesp.murilo.Models;

import java.util.Date;

public class RelationVote {
    private Candidate candidate;
    private Date voteDate;
    
    @SuppressWarnings("unused")
    private RelationVote() {
    }
    
    public RelationVote(Candidate candidate, Date voteDate) {
        this.candidate = candidate;
        this.voteDate = voteDate;
    }
    public Candidate getCandidate() {
        return candidate;
    }
    public void setCandidate(Candidate candidate) {
        this.candidate = candidate;
    }
    public Date getVoteDate() {
        return voteDate;
    }
    public void setVoteDate(Date voteDate) {
        this.voteDate = voteDate;
    }
    
    
}
