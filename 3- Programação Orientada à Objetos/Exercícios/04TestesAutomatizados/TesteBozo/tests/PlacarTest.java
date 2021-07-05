import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import static org.junit.Assert.*;

public class PlacarTest {

    private Placar placar;

    @Before
    public void setUp() throws Exception {
        placar = new Placar();
    }

    @After
    public void tearDown() throws Exception {
        placar = null;
    }

    @Test
    public void testAddPosicaoValida() throws Exception {
        placar.add(4, new int[] { 1, 3, 5, 3, 1 });
    }

    @Test(expected = BozoException.class)
    public void testAddPosicaoMenor() throws Exception {
        placar.add(0, new int[] { 1, 3, 5, 3, 1 });
    }

    @Test(expected = BozoException.class)
    public void testAddPosicaoMaior() throws Exception {
        placar.add(11, new int[] { 1, 3, 5, 3, 1 });
    }

    @Test
    public void testGetScoreCheio() throws Exception {

        placar.add(1, new int[] { 1, 1, 1, 1, 1 });
        placar.add(2, new int[] { 2, 2, 2, 2, 2 });
        placar.add(3, new int[] { 3, 3, 3, 3, 3 });
        placar.add(4, new int[] { 4, 4, 4, 4, 4 });
        placar.add(5, new int[] { 5, 5, 5, 5, 5 });
        placar.add(6, new int[] { 6, 6, 6, 6, 6 });
        placar.add(7, new int[] { 1, 1, 3, 3, 3 });
        placar.add(8, new int[] { 1, 2, 3, 4, 5 });
        placar.add(9, new int[] { 4, 4, 4, 4, 2 });
        placar.add(10, new int[] { 5, 5, 5, 5, 5 });

        assertEquals(210, placar.getScore());
    }

    @Test
    public void testGetScoreVazio() {
        assertEquals(0, placar.getScore());
    }

    @Test
    public void testFullHandQuadra() throws Exception {
        placar.add(7, new int[] { 1, 2, 2, 2, 2 });
        assertEquals(15, placar.getScore());
    }

    @Test
    public void testFullHandQuina() throws Exception {
        placar.add(7, new int[] { 3, 3, 3, 3, 3 });
        assertEquals(15, placar.getScore());
    }

    @Test
    public void testFullHandInvalido() throws Exception {
        placar.add(7, new int[] { 1, 2, 2, 3, 3 });
        assertEquals(0, placar.getScore());
    }

    @Test
    public void testSequenciaInvalida() throws Exception {
        placar.add(8, new int[] { 1, 2, 3, 4, 4 });
        assertEquals(0, placar.getScore());
    }

    @Test
    public void testQuadraInvalida() throws Exception {
        placar.add(9, new int[] { 1, 2, 3, 2, 1 });
        assertEquals(0, placar.getScore());
    }

    @Test
    public void testQuinaInvalida() throws Exception {
        placar.add(10, new int[] { 1, 2, 3, 2, 1 });
        assertEquals(0, placar.getScore());
    }

    @Test
    public void testToStringVazio() throws Exception {

        String placarVazio = "(1)    |  (7)  |    (4)\n" +
                             "-----------------------\n" +
                             "(2)    |  (8)  |    (5)\n" +
                             "-----------------------\n" +
                             "(3)    |  (9)  |    (6)\n" +
                             "-----------------------\n" +
                             " |       (10)       |\n";

        assertEquals(placarVazio, placar.toString());
    }

    @Test
    public void testToStringParcial() throws Exception {

        placar.add(3, new int[] { 3, 3, 1, 2, 3 });
        placar.add(7, new int[] { 5, 5, 6, 6, 6 });
        placar.add(9, new int[] { 2, 2, 4, 2, 2 });

        String placarVazio = "(1)    |  015  |    (4)\n" +
                             "-----------------------\n" +
                             "(2)    |  (8)  |    (5)\n" +
                             "-----------------------\n" +
                             "009    |  030  |    (6)\n" +
                             "-----------------------\n" +
                             " |       (10)       |\n";

        assertEquals(placarVazio, placar.toString());
    }

}