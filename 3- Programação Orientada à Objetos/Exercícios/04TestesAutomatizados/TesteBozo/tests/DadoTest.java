import org.junit.After;
import org.junit.BeforeClass;
import org.junit.Test;

import static org.junit.Assert.*;

public class DadoTest {

    private static Dado dado;

    @BeforeClass
    public static void setUpBeforeClass() throws Exception {
        dado = new Dado();
    }

    @After
    public void tearDown() throws Exception {
    }

    @Test
    public void getLado() {
        assertTrue(dado.getLado() >= 1 && dado.getLado() <= 6);
    }

    @Test
    public void rolar() {

        int ladoDeCima = 1;

        while (ladoDeCima <= 6) {
            if (dado.rolar() == ladoDeCima)
                ladoDeCima++;
        }

        assertTrue(dado.getLado() == 6);
    }

    @Test
    public void testToString1() {

        while (dado.getLado() != 1) {
            dado.rolar();
        }

        String string1 = "+-----+\n" +
                         "|     |\n" +
                         "|  *  |\n" +
                         "|     |\n" +
                         "+-----+\n";

        assertEquals(string1, dado.toString());
    }

    @Test
    public void testToString2() {

        while (dado.getLado() != 2) {
            dado.rolar();
        }

        String string2 = "+-----+\n" +
                         "|*    |\n" +
                         "|     |\n" +
                         "|    *|\n" +
                         "+-----+\n";

        assertEquals(string2, dado.toString());
    }

    @Test
    public void testToString3() {

        while (dado.getLado() != 3) {
            dado.rolar();
        }

        String string3 = "+-----+\n" +
                         "|*    |\n" +
                         "|  *  |\n" +
                         "|    *|\n" +
                         "+-----+\n";

        assertEquals(string3, dado.toString());
    }

    @Test
    public void testToString4() {

        while (dado.getLado() != 4) {
            dado.rolar();
        }

        String string4 = "+-----+\n" +
                         "|*   *|\n" +
                         "|     |\n" +
                         "|*   *|\n" +
                         "+-----+\n";

        assertEquals(string4, dado.toString());
    }

    @Test
    public void testToString5() {

        while (dado.getLado() != 5) {
            dado.rolar();
        }

        String string5 = "+-----+\n" +
                         "|*   *|\n" +
                         "|  *  |\n" +
                         "|*   *|\n" +
                         "+-----+\n";

        assertEquals(string5, dado.toString());
    }

    @Test
    public void testToString6() {

        while (dado.getLado() != 6) {
            dado.rolar();
        }

        String string6 = "+-----+\n" +
                         "|* * *|\n" +
                         "|     |\n" +
                         "|* * *|\n" +
                         "+-----+\n";

        assertEquals(string6, dado.toString());
    }

    @Test
    public void testToString7() {

        Dado personalizado = new Dado(12);

        while (personalizado.getLado() <= 6) {
            personalizado.rolar();
        }

        String string7 = "A função toString tem suporte para representar dados apenas de 1 a 6 lados\n";

        assertEquals(string7, personalizado.toString());
    }

    @Test
    public void testDadoPersonalizado1() {
        Dado personalizado = new Dado(3);
        assertNotNull(personalizado);
    }

}