package br.unesp.rc.modelo;

public class Curso {
    private String cod;
    private int vagas;
    private int candM;
    private int candF;

    public Curso() {
    }
    
    public Curso(String cod, int vagas, int candM, int candF) {
        this.cod = cod;
        this.vagas = vagas;
        this.candM = candM;
        this.candF = candF;
    }

    public String getCod() {
        return cod;
    }

    public void setCod(String cod) {
        this.cod = cod;
    }

    public int getVagas() {
        return vagas;
    }

    public void setVagas(int vagas) {
        this.vagas = vagas;
    }

    public int getCandM() {
        return candM;
    }

    public void setCandM(int candM) {
        this.candM = candM;
    }

    public int getCandF() {
        return candF;
    }

    public void setCandF(int candF) {
        this.candF = candF;
    }

    public Float getCandPorVaga(){
        return Float.valueOf((candM + candF)/vagas);
    }

    public Float getFemCandPct(){
        return Float.valueOf(candF/(candF + candM));
    }
}
