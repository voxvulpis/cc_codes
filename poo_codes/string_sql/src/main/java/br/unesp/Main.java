package br.unesp;

import java.net.MalformedURLException;

import br.unesp.model.SqlString;

public class Main {
    static String path = "/home/murilo/_code/poo_codes/string_sql/target/classes/br/unesp";
    static String clazzOne = "example.Livro";
    static String clazzTwo = "example.Carro";
    public static void main(String[] args) throws MalformedURLException, ClassNotFoundException {
        SqlString sqlString = new SqlString(path, clazzOne);
        SqlString sqlStringTwo = new SqlString(path, clazzTwo);

        System.out.println(sqlString);
        System.out.println(sqlStringTwo);
    }
}