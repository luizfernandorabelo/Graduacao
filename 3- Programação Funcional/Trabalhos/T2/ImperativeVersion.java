import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

class Main {

    private static void printFirstQuery(Record[] records, int n1) {
        int sum = 0;
        for (Record record : records) {
            if (record.getConfirmed() >= n1)
                sum += record.getActive();
        }
        System.out.println(sum);
    }

    private static void printSecondQuery(Record[] records, int n2, int n3) {
        n3 = n2 < n3 ? n2 : n3;
        Record.sortRecordsByActiveDescending(records, records.length - 1);
        Record.sortRecordsByConfirmedAscending(records, n2 - 1);
        for (int i = 0; i < n3; i++) {
            System.out.println(records[i].getDeaths());
        }
    }

    private static void printThirdQuery(Record[] records, int n4) {
        Record.sortRecordsByConfirmedDescending(records, records.length - 1);
        Record.sortRecordsByCountryAscending(records, n4 - 1);
        for (int i = 0; i < n4; i++) {
            System.out.println(records[i].getCountry());
        }
    }

    public static void main(String[] args) {
        Scanner stdinScanner = new Scanner(System.in);

        int n1 = stdinScanner.nextInt();
        int n2 = stdinScanner.nextInt();
        int n3 = stdinScanner.nextInt();
        int n4 = stdinScanner.nextInt();

        stdinScanner.close();

        Record[] records = Record.readRecordsFromFile();

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

    public static Record[] readRecordsFromFile() {
        Record [] records = new Record[MAX_RECORDS];
        try (Scanner fileScanner = new Scanner(new File(FILE_NAME))) {
            int index = 0;
            while (fileScanner.hasNextLine()) {
                String[] attributes = fileScanner.nextLine().split(DELIMITER);
                records[index++] = new Record(
                    attributes[0],
                    Integer.parseInt(attributes[1]),
                    Integer.parseInt(attributes[2]),
                    Integer.parseInt(attributes[3]),
                    Integer.parseInt(attributes[4])
                );
            }
            fileScanner.close();
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        return records;
    }

    public static void sortRecordsByActiveDescending(Record[] records, int endIndex) {
        for (int i = 0; i < endIndex; i++) {
            int k = i;
            for (int j = i + 1; j <= endIndex; j++) {
                if (records[j].active >= records[k].active) {
                    k = j;
                }
            }
            swapRecords(records, k, i);
        }
    }

    public static void sortRecordsByConfirmedAscending(Record[] records, int endIndex) {
        for (int i = 0; i < endIndex; i++) {
            int k = i;
            for (int j = i + 1; j <= endIndex; j++) {
                if (records[j].confirmed < records[k].confirmed) {
                    k = j;
                }
            }
            swapRecords(records, k, i);
        }
    }

    public static void sortRecordsByConfirmedDescending(Record[] records, int endIndex) {
        for (int i = 0; i < endIndex; i++) {
            int k = i;
            for (int j = i + 1; j <= endIndex; j++) {
                if (records[j].confirmed >= records[k].confirmed) {
                    k = j;
                }
            }
            swapRecords(records, k, i);
        }
    }

    public static void sortRecordsByCountryAscending(Record[] records, int endIndex) {
        for (int i = 0; i < endIndex; i++) {
            int k = i;
            for (int j = i + 1; j <= endIndex; j++) {
                if (records[j].country.compareTo(records[k].country) < 0) {
                    k = j;
                }
            }
            swapRecords(records, k, i);
        }
    }

    private static void swapRecords(Record[] records, int i, int j) {
        Record tmp = records[i];
        records[i] = records[j];
        records[j] = tmp;
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
