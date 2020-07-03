using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Samples.ManagedUWP.Helpers
{

    public static class WordGenerator
    {
        public static string Generate()
        {
            Random rnd = new Random();
            int length = rnd.Next(3, 10);
            return Generate(length);
        }


        public static string Generate(int length)
        {
            string word = "";
            Random rnd = new Random();
            string[] consonants = { "b", "c", "d", "f", "g", "h", "j", "k", "l", "m", "n", "p", "q", "r", "s", "t", "v", "w", "x", "y", "z" };
            string[] vowels = { "a", "e", "i", "o", "u" };

            if (length != 0)
            {

                // Generate the word in consonant / vowel pairs
                while (word.Length < length)
                {
                    if (length != 1)
                    {
                        // Add the consonant
                        string consonant = GetRandomLetter(rnd, consonants);

                        if (consonant == "q" && word.Length + 3 <= length)
                        // check +3 because we'd add 3 characters in this case, the "qu" and the vowel.  Change 3 to 2 to allow words that end in "qu"
                        {
                            word += "qu";
                        }
                        else
                        {
                            while (consonant == "q")
                            {
                                // Replace an orphaned "q"
                                consonant = GetRandomLetter(rnd, consonants);
                            }

                            if (word.Length + 1 <= length)
                            {
                                // Only add a consonant if there's enough room remaining
                                word += consonant;
                            }
                        }
                    }

                    if (word.Length + 1 <= length)
                    {
                        // Only add a vowel if there's enough room remaining
                        word += GetRandomLetter(rnd, vowels);
                    }
                }
            }
            return word;
        }

        private static string GetRandomLetter(Random rnd, string[] letters)
        {
            return letters[rnd.Next(0, letters.Length - 1)];
        }
    }
}
