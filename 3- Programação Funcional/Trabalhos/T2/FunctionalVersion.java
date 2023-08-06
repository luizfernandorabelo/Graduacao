import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.Arrays;
import java.util.Comparator;
import java.util.List;

class Main {

    private static void printFirstQuery(List<Record> records, int n1) {
        int result = records
            .stream()
            .filter(r -> r.getConfirmed() >= n1)
            .map(r -> r.getActive())
            .reduce(0, Integer::sum);
        System.out.println(result);
    }

    private static void printSecondQuery(List<Record> records, int n2, int n3) {
        Integer result[] = records
            .stream()
            .sorted(Comparator.comparing(Record::getActive).reversed())
            .limit(n2)
            .sorted(Comparator.comparing(Record::getConfirmed))
            .limit(n3)
            .map(r -> r.getDeaths())
            .toArray(Integer[]::new);
        printSecondQuery(result, result.length, 0);
    }

    public static void printSecondQuery(Integer[] result, int n, int i) {
        if (i == n) return;
        System.out.println(result[i]);
        printSecondQuery(result, n, i + 1);
    }

    public static void printThirdQuery(List <Record> records, int n4) {
        String result[] = records
            .stream()
            .sorted(Comparator.comparing(Record::getConfirmed).reversed())
            .limit(n4)
            .sorted(Comparator.comparing(Record::getCountry))
            .map(r -> r.getCountry())
            .toArray(String[]::new);
        printThirdQuery(result, result.length, 0);
    }

    public static void printThirdQuery(String[] result, int n, int i) {
        if (i == n) return;
        System.out.println(result[i]);
        printThirdQuery(result, n, i + 1);
    }

    public static void main(String[] args) {
        Scanner stdinScanner = new Scanner(System.in);

        int n1 = stdinScanner.nextInt();
        int n2 = stdinScanner.nextInt();
        int n3 = stdinScanner.nextInt();
        int n4 = stdinScanner.nextInt();

        stdinScanner.close();

        List<Record> records = Record.readRecordsFromFile();

        printFirstQuery(records, n1);
        printSecondQuery(records, n2, n3);
        printThirdQuery(records, n4);
    }
}

class Record {
    private static final int MAX_RECORDS = 200;
    private static final String FILE_NAME = "dados.csv";
    private static final String DELIMITER = ",";

    private String country;
    private int confirmed;
    private int deaths;
    private int recovery;
    private int active;

    public Record(String country, int confirmed, int deaths, int recovery, int active) {
        this.country = country;
        this.confirmed = confirmed;
        this.deaths = deaths;
        this.recovery = recovery;
        this.active = active;
    }

    public static void readRecordsFromFileRec(Scanner fileScanner, Record[] records, int i) {
        if (!fileScanner.hasNextLine()) return;
        String[] attributes = fileScanner.nextLine().split(DELIMITER);
        records[i] = new Record(
            attributes[0],
            Integer.parseInt(attributes[1]),
            Integer.parseInt(attributes[2]),
            Integer.parseInt(attributes[3]),
            Integer.parseInt(attributes[4])
        );
        readRecordsFromFileRec(fileScanner, records, i + 1);
    }

    public static List<Record> readRecordsFromFile() {
        Record [] records = new Record[MAX_RECORDS];
        try (Scanner fileScanner = new Scanner(new File(FILE_NAME))) {
            readRecordsFromFileRec(fileScanner, records, 0);
            fileScanner.close();
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        return Arrays.asList(records);
    }

    public String getCountry() {
        return country;
    }

    public int getConfirmed() {
        return confirmed;
    }

    public int getDeaths() {
        return deaths;
    }

    public int getRecovery() {
        return recovery;
    }

    public int getActive() {
        return active;
    }
}
