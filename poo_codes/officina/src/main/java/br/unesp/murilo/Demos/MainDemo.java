package br.unesp.murilo.Demos;

import br.unesp.murilo.Models.Car;
import br.unesp.murilo.Models.SemiTruck;
import br.unesp.murilo.Repos.Queue;
import br.unesp.murilo.Util.QueueUtils;

public class MainDemo {

    public static void runDemo(){
        Queue queue = new Queue();

        queue.add(new Car(5, "Fox"));
        queue.add(new Car(1, "F1"));
        queue.add(new Car(9, "Combi?"));
        queue.add(new Car(2, "Porsche"));
        queue.add(new Car(5, "Golf"));

        queue.add(new SemiTruck(4, "Tipo1"));
        queue.add(new SemiTruck(5, "Tipo2"));
        queue.add(new SemiTruck(9, "Tipo3"));
        queue.add(new SemiTruck(3, "Tipo4"));


        QueueUtils.print(queue);

        queue.popOff();

        QueueUtils.print(queue);
    }


}
