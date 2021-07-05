import org.junit.BeforeClass;
import org.junit.Test;

import static org.junit.Assert.*;

public class RolaDadosTest {

    private static RolaDados rolaDados;

    @BeforeClass
    public static void setUpBeforeClass() {
        rolaDados = new RolaDados(5);
    }

    @Test
    public void testRolarTodos() {

        int [] valoresAnteriores = rolaDados.rolar(new boolean[] { false, false, false, false, false });
        int [] valoresNovos = rolaDados.rolar();

        while (valoresAnteriores.equals(valoresNovos)) {
            valoresNovos = rolaDados.rolar();
        }

        assertNotSame(valoresAnteriores, valoresNovos);
    }

    @Test
    public void testRolarBoolean() {

        int [] valoresAnteriores = rolaDados.rolar(new boolean[] { false, false, false, false, false });
        int [] valoresNovos = rolaDados.rolar(new boolean[] { true, false, true, false, true });

        while (valoresAnteriores.equals(valoresNovos)) {
            valoresNovos = rolaDados.rolar();
        }

        assertNotSame(valoresAnteriores, valoresNovos);
    }

    @Test
    public void testRolarString() {

        int [] valoresAnteriores = rolaDados.rolar(new boolean[] { false, false, false, false, false });
        int [] valoresNovos = rolaDados.rolar("2 4");

        while (valoresAnteriores.equals(valoresNovos)) {
            valoresNovos = rolaDados.rolar();
        }

        assertNotSame(valoresAnteriores, valoresNovos);
    }

    @Test
    public void testToStringInicial() {

        RolaDados rolaDados1 = new RolaDados(5);

        rolaDados1.rolar(new boolean[] { false, false, false, false, false });

        String stringInicial = "1      \t2      \t3      \t4      \t5      \t\n" +
                               "+-----+\t+-----+\t+-----+\t+-----+\t+-----+\t\n" +
                               "|     |\t|     |\t|     |\t|     |\t|     |\t\n" +
                               "|  *  |\t|  *  |\t|  *  |\t|  *  |\t|  *  |\t\n" +
                               "|     |\t|     |\t|     |\t|     |\t|     |\t\n" +
                               "+-----+\t+-----+\t+-----+\t+-----+\t+-----+\t\n";

        assertEquals(stringInicial, rolaDados1.toString());
    }

    @Test
    public void testConstrutorInterrupt() {
        Thread.currentThread().interrupt();
        RolaDados rolaDados2 = new RolaDados(5);
        assertNotNull(rolaDados2);
    }
}