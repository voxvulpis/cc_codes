package br.unesp.rc.modelo;

public class Pessoa {
    private String nome;
    private String cpf;
    private Float salario;

    public Pessoa() {
    }
    
    public Pessoa(String nome, String cpf, Float salario) {
        this.nome = nome;
        this.cpf = cpf;
        this.salario = salario;
    }

    public String getNome() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public String getCpf() {
        return cpf;
    }

    public void setCpf(String cpf) {
        this.cpf = cpf;
    }

    public Float getSalario() {
        return salario;
    }

    public void setSalario(Float salario) {
        this.salario = salario;
    }
    
    
}
