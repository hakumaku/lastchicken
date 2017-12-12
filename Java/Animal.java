import java.util.Scanner;
import java.util.*;

/*
 * public:
 *	visible and can be called from other objects of other types.
 *
 * static:
 *	can be called without creating an object.
 *
 * private:
 *	only the class where it is declared can see it.
 *
 * protected:
 *	package private + subclasses or package member.
 *
 * package private(default):
 *	seen and used by the package where it was declared.
 */
public class Animal {

	// final is similar to const.
	public static final double FAVNUMBER = 1.6180;

	private String name;
	private int weight;
	private boolean hasOwner = false;
	/*
	 * Note:
	 *	byte-8bits
	 *	char-16bits
	 */
	private byte age;
	private long uniqueID;
	private char favoriteChar;
	private double speed;
	private float height;

	protected static int numberOfAnimals = 0;
	
	static Scanner userInput = new Scanner(System.in);

	/* Constructor */
	public Animal() {
		numberOfAnimals++;

		int sumOfNumbers = 5 + 1;
		System.out.println("5 + 1 = " + sumOfNumbers);

		int diffOfNumbers = 5 - 1;
		System.out.println("5 - 1 = " + diffOfNumbers);

		int multOfNumbers = 5 * 1;
		System.out.println("5 * 1 = " + multOfNumbers);

		int divOfNumbers = 5 / 1;
		System.out.println("5 / 1 = " + divOfNumbers);

		int modOfNumbers = 5 % 3;
		System.out.println("5 % 3 = " + modOfNumbers);

		System.out.println("Enter the name: \n");
		/*
		 * hasNextInt
		 * nextInt
		 * hasNextFloat
		 * nextFloat
		 * hasNextDouble
		 * nextDouble
		 * hasNextBoolean
		 * nextBoolean
		 * hasNextByte
		 * nextByte
		 */
		if (userInput.hasNextLine()) {
			this.setName(userInput.nextLine());
		}

		this.setFavoriteColor();
		this.setUniqueID();
	}

	protected static void countTo(int startingNumbr) {

		for (int i = startingNumbr; i <= 100; i++) {
			
			if (i == 90) continue;

			System.out.println(i);

		}

	}

	protected static String printNumbers(int maxNumbers) {

		int i = 1;

		while (i < (maxNumbers / 2)) {

			System.out.println(i);
			i++;

			if (i == (maxNumbers/2)) break;
		}

		Animal.countTo(maxNumbers/2);

		return "End of printNumbers";
	}

	protected static void guessMyNumber() {
		int number;

		do {
			System.out.println("Guess Number up to 100");

			while (!userInput.hasNextInt()) {

				String numberEntered = userInput.next();
				System.out.printf("%s is not a number.\n", numberEntered);

			}

			number = userInput.nextInt();

		} while (number != 50);
	}

	public String makeSound() {

		return "Grrrr";

	}

	/* polymorphism */
	public static void speakAnimal(Animal randAnimal) {

		System.out.println("Animal says " + randAnimal.makeSound());

	}

	public static void main(String[] args) {
		// Constructor
		Animal theAnimal = new Animal();

		int[] favoriteNumbers = new int[20];
		favoriteNumbers[0] = 100;

		String[] stringArray = {"Random", "Words", "Here"};

		for (String word: stringArray) {

			System.out.println(word);

		}

		String[][][] arrayName = {
			{
				{"000"}, {"100"}, {"200"}
			},
			{
				{"010"}, {"110"}, {"210"}
			},
			{
				{"020"}, {"120"}, {"220"}
			},
			{
				{"030"}, {"130"}, {"230"}
			}
		};

		for (int i = 0; i < arrayName.length; i++) {

			for (int j = 0; j < arrayName[i].length; j++) {

				for (int k = 0; k < arrayName[i][j].length; k++) {
					System.out.println("| " + arrayName[i][j][k] + " ");
				}
			}
		}

		String[] cloneOfArray = Arrays.copyOf(stringArray, 3);

		System.out.println(Arrays.toString(cloneOfArray));

		System.out.println(Arrays.binarySearch(cloneOfArray, "020"));
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public double getSpeed() {
		return speed;
	}
	public void setSpeed() {
		this.speed = speed;
	}

	public int getWeight() {
		return weight;
	}
	public void setWeight(int weight) {
		this.weight = weight;
	}

	public boolean isHasOwner() {
		return hasOwner;
	}
	public void setHasOwner(boolean hasOwner) {
		this.hasOwner = hasOwner;
	}

	public byte getAge() {
		return age;
	}
	public void setAge(byte age) {
		this.age = age;
	}

	public long getUniqueId() {
		return uniqueID;
	}

	/* Override */
	public void setUniqueID(long uniqueID) {
		this.uniqueID = uniqueID;
		System.out.println("Unique ID set to: " + this.uniqueID);
	}
	/* Override(parameters are different) */
	public void setUniqueID() {
		long minNumber = 1;
		long maxNumber = 1000000;

		this.uniqueID = minNumber + (long)(Math.random() * ((maxNumber - minNumber) + 1));
		// Byte.toString
		// Integer.toString
		String stringNumber = Long.toString(maxNumber);

		// Integer.parseLong
		// Integer.parseFloat
		int numberString = Integer.parseInt(stringNumber);
		System.out.println("Unique ID set to: " + this.uniqueID);
	}

	public char getFavoriteChar() {
		return favoriteChar;
	}
	public void setFavoriteColor(char favoriteChar) {
		this.favoriteChar = favoriteChar;
	}
	public void setFavoriteColor() {
		int randomNumber = (int)(Math.random() * 126) + 1;

		this.favoriteChar = (char)randomNumber;

		if (randomNumber == 32) {

			System.out.println("Favorite character set to Space.");

		} else if (randomNumber == 10) {

			System.out.println("Favorite character set to Newline.");

		} else {

			System.out.println("Favorite character set to " + this.favoriteChar);

		}

		if ((randomNumber > 97) && (randomNumber < 122)) {

			System.out.println("Favorite character is a lowercase letter.");

		}
		if (((randomNumber > 97) && (randomNumber < 122))
				|| ((randomNumber > 64) && (randomNumber < 91))) {

			System.out.println("Favorite character is a letter.");

		}

		int whichIsBigger = (50 > randomNumber) ? 50 : randomNumber;

		switch (randomNumber) {
			case 8:
				System.out.println("Favorite character set to backspace.");
				break;

			case 10:
			case 11:
			case 12:
				System.out.println("10 to 12 action.");
				break;

			default:
				System.out.println("default action.");
				break;
		}
	}

}

