package br.murilo.controller;

public class VectorUtils {

    public VectorUtils() {
    }


    public static void enumerate(int vec[]){

        for (int i = 0; i < vec.length; i++) {
            vec[i] = i;
        }
    }



    public static void print(int vec[]){

        for(int value : vec){
            System.out.println(value);
        }
    }
}
