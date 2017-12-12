/**
 * Local Sequence Alignment
 * (Smith-Waterman Algorithm).
 *
 * 1) Build a table.
 *	m = A.length + 1
 *	n = B.length + 1
 *	table[i][j] = 0, where i == 0 || j == 0
 *	table[i][j] = max(diag, top, left, 0)
 *	where diag = MATCH || MISMATCH,
 *	top = GAP_A, and left = GAP_B
 *	(There can be GAP_EXTENSION in some implementation.)
 *
 * 2) Backtrack it from the largest value in the table.
 *
 */
import java.io.FileReader;
import java.io.BufferedReader;
import java.io.IOException;
import java.util.ArrayList;
import java.io.FileOutputStream;
import java.io.BufferedWriter;
import java.io.OutputStreamWriter;
import java.io.Writer;

class Bar {

	private static final String DEFAULT_DB_PATH = "sample/Test/TestDB.fa";
	private static final String[] DEFAULT_QUERY_PATH = {
		"sample/Test/TestQuery1.fa", "sample/Test/TestQuery2.fa", "sample/Test/TestQuery3.fa"
	};
	private static final int MATCH = 5;
	private static final int MISMATCH = -4;
	private static final int GAP = -10;

	private String dbInfo;
	private String dbString;
	private String queryInfo;
	private String queryString;
	private String outFile;

	private int[][] scoreMatrix;
	private String alignedQueryString;
	private String alignedDbString;

	public void setScore(int i, int j, int value) {
		if (value < 0) {
			value = 0;
		}
		scoreMatrix[i][j] = value;
	}

	public Bar(String[] path) {
		setOutFile(path[2]);

		String[] data = readDataFile(path[0]);

		setdbInfo(path[0] + "(" + data[0] + ")");
		setdbString(data[1]);

		data = readDataFile(path[1]);

		setQueryInfo(path[1] + "(" + data[0] + ")");
		setQueryString(data[1]);
	}

	private static String[] readDataFile(String path) {
		String[] data = new String[2];

		try (BufferedReader br = new BufferedReader(new FileReader(path))) {
			StringBuilder sb = new StringBuilder();
			data[0] = br.readLine();

			if (data[0] != null) {
				String line = null;

				while ((line = br.readLine()) != null) {
					sb.append(line);
				}

				data[1] = sb.toString().trim();
			}

		} catch (Exception e) {
			e.printStackTrace();
			System.err.println("In readDataFile: Either path is wrong or reading lines.");
		}

		return data;
	}

	public void computeLocalAlignment(boolean display) {
		long startTime = 0;
		long endTime = 0;
		double elapsed = 0;
		double total = 0;

		System.out.println("Building a table...");
		startTime = System.currentTimeMillis();
		buildTable();
		endTime = System.currentTimeMillis();
		elapsed = (double)(endTime - startTime) / 1000;
		System.out.format("Done: %.4f\n", elapsed);
		total = elapsed;

		System.out.println("Backtracking...");
		startTime = System.currentTimeMillis();
		backtrackTable();
		endTime = System.currentTimeMillis();
		elapsed = (double)(endTime - startTime) / 1000;
		System.out.format("Done: %.4f\n", elapsed);
		total += elapsed;

		System.out.println("Writing result on: " + getOutFile());
		writeResult();
		System.out.println("Done writing");
		System.out.format("Task completed: %.4f\n", total);

		if (display) {
			displayScoreMatrix();
		}
		
		long usedMem = Runtime.getRuntime().totalMemory() - Runtime.getRuntime().freeMemory();
		double usedMemMib = (double)usedMem / (1024*1024);
		System.out.format("Java Approximate Memory Usage: %.3f Mib\n", usedMemMib);
	}

	private void buildTable() {
		if (dbString == null || queryString == null) {
			System.err.println("Data has not been initialized.");
			return;
		}

		int m = queryString.length() + 1;
		int n = dbString.length() + 1;

		if (m < 0 || n < 0) {
			System.err.println(
				"It seems overflow has occured.\n" +
				"m: " + m +
				" n: " + n
			);
		} else {
			System.out.println("m: " + m + " n: " + n);
		}

		scoreMatrix = new int[m][n];

		for (int i = 1; i < m; i++) {
			for (int j = 1; j < n; j++) {
				int diag = scoreMatrix[i-1][j-1];
				int top = scoreMatrix[i-1][j] + GAP;
				int left = scoreMatrix[i][j-1] + GAP;

				if (queryString.charAt(i-1) == dbString.charAt(j-1)) {
					diag += MATCH;

				} else {
					diag += MISMATCH;
				}

				if (diag > top && diag > left) {
					setScore(i, j, diag);

				} else if (top > left) {
					setScore(i, j, top);

				} else {
					setScore(i, j, left);
				}
			}
		}
	}

	public int[] searchMaxInMatrix() {
		int[] pos = new int[2];
		int m = scoreMatrix.length;
		int n = scoreMatrix[0].length;
		int max = 0;
		
		for (int i = 1; i < m; i++) {
			for (int j = 1; j < n; j++) {
				int temp = scoreMatrix[i][j];
				if (max < temp) {
					max = temp;
					pos[0] = i;
					pos[1] = j;
				}
			}
		}

		return pos;
	}

	public boolean isFromDiag(int i, int j) {
		return (queryString.charAt(i-1) == dbString.charAt(j-1))
				|| (scoreMatrix[i][j]-scoreMatrix[i-1][j-1]) == MISMATCH;
	}
	public boolean isFromTop(int i, int j) {
		return (scoreMatrix[i][j]-scoreMatrix[i-1][j]) == GAP;
	}
	public boolean isFromLeft(int i, int j) {
		return (scoreMatrix[i][j]-scoreMatrix[i][j-1]) == GAP;
	}

	public void displayScoreMatrix() {
		int m = scoreMatrix.length;
		int n = scoreMatrix[0].length;

		int[] pos = searchMaxInMatrix();
		int score = scoreMatrix[pos[0]][pos[1]];

		System.out.println("Score: " + score);
		int len = String.valueOf(score).length() + 1;

		for (int i = 0; i < m; i++) {
			StringBuilder line = new StringBuilder();

			for (int j = 0; j < n; j++) {
				line.append(String.format("%" + len + "d", scoreMatrix[i][j]));
			}
			System.out.println(line);
		}
		
	}

	public void backtrackTable() {
		StringBuilder alignedQuery = new StringBuilder();
		StringBuilder alignedDb = new StringBuilder();
		int[] pos = searchMaxInMatrix();

		int i = pos[0];
		int j = pos[1];

		while (i > 0 || j > 0) {

			if (scoreMatrix[i-1][j-1] == 0) {
				alignedQuery.insert(0, queryString.charAt(i-1));
				alignedDb.insert(0, dbString.charAt(j-1));
				break;

			} else if (isFromDiag(i, j)) {
				alignedQuery.insert(0, queryString.charAt(i-1));
				alignedDb.insert(0, dbString.charAt(j-1));
				i--;
				j--;

			} else if (isFromTop(i, j)) {
				alignedQuery.insert(0, queryString.charAt(i-1));
				alignedDb.insert(0, '-');
				i--;

			} else {
				alignedQuery.insert(0, '-');
				alignedDb.insert(0, dbString.charAt(j-1));
				j--;
			}
		}
		setAlignedQueryString(alignedQuery.toString());
		setAlignedDbString(alignedDb.toString());
	}

	public void writeResult() {
		FileOutputStream fs = null;
		try {
			fs = new FileOutputStream(getOutFile());

		} catch (Exception e) {
			e.printStackTrace();
			System.err.println("Opening a file has failed: " + getOutFile());
		}

		try (Writer writer = new BufferedWriter(new OutputStreamWriter(fs, "utf-8"))) {
			StringBuilder basicFormat = new StringBuilder();
			basicFormat.append("DB: " + getdbInfo());
			basicFormat.append(System.lineSeparator());

			basicFormat.append("Query: " + getQueryInfo());
			basicFormat.append(System.lineSeparator());
			basicFormat.append(System.lineSeparator());

			basicFormat.append("<Alignment>");
			basicFormat.append(System.lineSeparator());
			basicFormat.append(System.lineSeparator());

			basicFormat.append("DB Sequence:");
			basicFormat.append(System.lineSeparator());
			basicFormat.append(getAlignedDbString());
			basicFormat.append(System.lineSeparator());

			basicFormat.append("Query Sequence:");
			basicFormat.append(System.lineSeparator());
			basicFormat.append(getAlignedQueryString());
			basicFormat.append(System.lineSeparator());

			writer.write(basicFormat.toString());

		} catch (Exception e) {
			e.printStackTrace();
			System.err.println("Problem during writing on: " + getOutFile());
		}
	}

	public String getAlignedQueryString() {
		return alignedQueryString;
	}
	public void setAlignedQueryString(String alignedQueryString) {
		this.alignedQueryString = alignedQueryString;
	}

	public String getAlignedDbString() {
		return alignedDbString;
	}
	public void setAlignedDbString(String alignedDbString) {
		this.alignedDbString = alignedDbString;
	}

	public String getdbInfo() {
		return dbInfo;
	}
	public void setdbInfo(String dbInfo) {
		this.dbInfo = dbInfo;
	}

	public String getdbString() {
		return dbString;
	}
	public void setdbString(String dbString) {
		this.dbString = dbString;
	}

	public String getOutFile() {
		return outFile;
	}
	public void setOutFile(String outFile) {
		this.outFile = outFile;
	}

	public String getQueryInfo() {
		return queryInfo;
	}
	public void setQueryInfo(String queryInfo) {
		this.queryInfo = queryInfo;
	}

	public String getQueryString() {
		return queryString;
	}
	public void setQueryString(String queryString) {
		this.queryString = queryString;
	}

	/* MAIN */
	public static void main(String[] args) {
		if (args.length < 3) {
			System.out.println(
				"Not enough command-line arguments. " +
				"Try using default arguments."
			);
			args = new String[]{ DEFAULT_DB_PATH, DEFAULT_QUERY_PATH[0], "out.txt" };
		}

		Bar foo = new Bar(args);
		foo.computeLocalAlignment(false);
	}
}

