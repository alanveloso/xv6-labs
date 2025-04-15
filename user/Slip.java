public class SlipExample {
    public static void main(String[] args) {
        System.out.println("Antes do slip...");
        
        try {
            Thread.sleep(2000); // pausa por 2000 milissegundos (2 segundos)
        } catch (InterruptedException e) {
            System.out.println("A thread foi interrompida!");
        }

        System.out.println("Depois do slip.");
    }
}
