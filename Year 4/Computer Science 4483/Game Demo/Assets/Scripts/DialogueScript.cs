using UnityEngine;
using UnityEngine.UI;
using System.IO;
using System;
using UnityEngine.SceneManagement;

public class DialogueScript : MonoBehaviour
{
    // Variables
	public Text topText;
	public Text bottomText;
	public GameObject s1;
	public GameObject s2;
	public GameObject s3;
	public GameObject s4;
	public GameObject s5;
	public GameObject s6;
	public GameObject s7;
	public GameObject s8;
	public GameObject s9;
	public GameObject s10;
	public int type = 0;
	int count = 0;
	public int level;
	public Material[] materials;

	// Load which dialogue to use
	void Start ()
	{
		int type = 0;
		string path = "Assets/Resources/story.dat";
		StreamReader read = new StreamReader (path);
		string pType = read.ReadLine ();

		int c = Convert.ToInt32 (pType);
		// Close the file
		read.Close ();
		print (c);
		level = c;
		if (c <= 0) {
			this.type = 1;
			c *= -1;
			level = c;
		}
	}

    // Based on which level display respective dialogue
	void Update ()
	{
		
		if (Input.GetKeyDown ("space")) {
			count++;

		}
		if (level == 0) {
			DialogueZero (count);
		} else if (level == 1) {
			DialogueOne (type, count);
		} else if (level == 2) {
			DialogueTwo (type, count);
		} else if (level == 3) {
			DialogueThree (type, count);
		} else if (level == 4) {
			DialogueFour (type, count);
		} else if (level == 5) {
			DialogueFive (type, count);
		}
	}

	void Exit (int index)
	{
		SceneManager.LoadScene (index);
	}

	// Update is called once per frame
	void DialogueZero (int count)
	{

		switch (count) {
		// Fourth row
		case 21:
			Exit (2);
			break;

		// Fifth row / front row
		case 20:
			s7.SetActive (true);
			s5.SetActive (false);
			topText.text = "Vinny: Let the mission begin then.";
			break;
		case 19:
			s8.SetActive (false);
			s4.SetActive (true);
			bottomText.text = "Akane: Well, what're we waiting for then. Let's go already";
			break;
		case 18:
			s1.SetActive (false);
			s5.SetActive (true);
			topText.text = "Lonk: It's a risky plan, but if it means we can live for more than a few days, " +
			"I'd say it's worth it.";
			break;
		case 17:
			s8.SetActive (true);
			bottomText.text = "Vinny: Alright guys, when I press this button, there is no going back";
			break;
		case 16:
			topText.text = "Only time will tell folks, but in the mean time let's look at the stock market.";
			break;
		case 15:
			topText.text = "Will they be able to save earth from pending doom? " +
			"Or is it all just a pipe dream and we should start counting down to our final moments?";
			break;
		case 14:
			s1.SetActive (true);
			topText.text = "Hello everyone, I'm Someone Whoyoudontknow live here at the axis satellite launch. " +
			"These brave folks have decided to be humanity's last hope";
			break;
		case 13:
			s8.SetActive (false);
			s5.SetActive (false);
			topText.text = "Later that evening...";
			bottomText.text = "Satellite Launch";
			break;
		case 12:
			s4.SetActive (false);
			s8.SetActive (true);
			bottomText.text = "Vinny: We will not be answering any questions as we need to prepare for launch.";
			break;
		case 11:
			topText.text = "Lonk: We're going to show them aliens that we aren't scared of their threats";
			break;
		case 10:
			topText.text = "Lonk: Not only that, but we've made three of them ready for launch tonight";
			break;
	
		case 9:
			bottomText.text = "Akane: The Space Paddle-Ball, is our answer to the aliens threats. " +
			"It is a remote controlled satellite, which uses a heavy ball to eliminate anything it" +
			" collides with";
			break;
		case 8:
			s7.SetActive (false);
			s5.SetActive (true);
			topText.text = "How's it going, I'm Lonk, the last of the three members";
			break;
		case 7:
			s4.SetActive (true);
			bottomText.text = "Hi everyone, I'm Akane one of the three members of Axis corp.";
			break;
		case 6:
			topText.text = "Vinny: Akane, Lonk, bring out the Space Paddle-Ball";
			break;
		case 5:
			s7.SetActive (true);
			topText.text = "Thank you all for coming, I'm Vinny the head of Axis corp. With the news " +
			"about earth's impending destruction, we've made some revisions " +
			"to the satellite we're revealing here";
			break;
		case 4:
			s1.SetActive (false);
			topText.text = "Later that day...";
			bottomText.text = "Axis Corporation Satellite reveal";
			break;
		case 3:
			topText.text = "In the meantime, this has been Someone Whoyoudontknow for News 1131 signing off.";
			break;
		case 2:
			topText.text = "This will be interesting as the Axis corporation was due to unveil a new satellite later today.";
			break;
		case 1:
			topText.text = "The aliens are coming to blow up the planet, due to them being fed up with " +
			"our satellites interfering with them";
			break;
		case 0:
			topText.text = "We interupt your regularly scheduled broadcast for this breaking news. " +
			"WE ON EARTH ARE DOOMED, as alien invaders have announced that they are going to destory Earth.";
			bottomText.text = " ";
			s1.SetActive (true);
			break;
		}
			
	}


	void DialogueOne (int type, int count)
	{
		

		if (type == 0) {
			switch (count) {
			// Fourth row
			case 11:
				Exit (4);
				break;

			// Fifth row / front row
			case 10:
				topText.text = "Mission: Defeat All Enemies";
				bottomText.text = " ";
				break;
			case 9:
				topText.text = "CONTROLS\n" +
				"Remember, you need to bounce the ball off of the paddle\n";
				bottomText.text = "The ball will damage enemies upon contact";
				break;
			case 8:
				topText.text = "CONTROLS\n" +
				"Before launching the ball, you can open up the pause menu by pressing 'esc'";
				bottomText.text = "If the ball gets stuck some how, you can reset by pressing 'esc' during play, though there is a penalty\n";
				break;
			case 7:
				s5.SetActive (false);
				s8.SetActive (false);
				topText.text = "CONTROLS\n" +
				"To move the paddle, you press the left and right keys\n"; 
				bottomText.text = "To initially shoot the ball press the space button\n";
				break;
			case 6:
				topText.text = "Lonk: Listen closely boss, this is the fifteenth time that" +
				" you've made me remind you the controls";
				break;
			case 5:
				bottomText.text = "Vinny: Well, enough chit chat let's get started. " +
				"Lonk, how do you use this thing?";
				break;
			case 4:
				topText.text = "Lonk: Nah, these guys will be easy. We're going to beat them in one hit ";
				break;
			case 3:
				s4.SetActive (false);
				s8.SetActive (true);
				bottomText.text = "Vinny: Just because this is the first wave " +
				"doesn't mean it'll be easy, it may take multiple hits to beat these guys ";
				break;
			case 2:
				topText.text = "Lonk: Well, it's based on the arcade game involving space invaders " +
				"and since this is the first wave, these guys will be weak";
				break;
			case 1:
				s4.SetActive (true);
				bottomText.text = "Akane: Lonk, how would you have made a simulator? " +
				"We don't even know anything about the space invaders!";
				break;
			case 0:
				s5.SetActive (true);
				topText.text = "Lonk: Since it will take a while before we run into the enemies " +
				"I think we should do some training using the simulator I made";
				bottomText.text = " ";
				break;
			}
		} else {
			switch (count) {
			// Fourth row
			case 10:
				Exit (2);
				break;
			case 9:
				topText.text = "Vinny: Everyone to their stations, let's show these aliens we mean business";
				break;
			case 8:
				s6.SetActive (false);
				s4.SetActive (true);
				bottomText.text = "Akane: Woohoo, it's finally party time!";
				break;
			case 7:
				s3.SetActive (false);
				s7.SetActive (true);
				topText.text = "Vinny: Lonk you numbskull, those are the space invaders";
				break;
			case 6:
				bottomText.text = "Lonk: Uhhhh, it looks like a bunch of orange blobs are attacking";
				break;
			case 5:
				s7.SetActive (false);
				s3.SetActive (true);
				topText.text = "Akane: Well, is it party time, or was it just a little rock?";
				break;
			case 4:
				bottomText.text = "Lonk: Checking the collision now";
				break;
			case 3:
				s3.SetActive (false);
				s7.SetActive (true);
				topText.text = "Vinny: Alright, enough arguing you two. " +
				"The satellite's been hit, we need to see what it was.";
				break;
			case 2:
				bottomText.text = "Lonk: But in all seriousness, there won't be any nice space background " +
					"in the real thing, as getting fancy camera's was not cheap.";
				break;
			case 1:
				s6.SetActive (true);
				bottomText.text = "Lonk: Sorry, next time I'll make sure that there are rainbows" +
				" and unicorns on the background. That way you won't focus on the mission";
				break;
			case 0:
				s3.SetActive (true);
				topText.text = "Akane: Lonk, you weren't kidding when you said it'd be easy." +
				" Though one complaint for your simulator is that it needs a nice background";
				bottomText.text = " ";
				break;
			}
		}
	}

	void DialogueTwo (int type, int count)
	{
		

		if (type == 0) {
			switch (count) {
			// Fourth row
			case 5:
				Exit (4);
				break;

			// Fifth row / front row
			case 4:
				s4.SetActive (false);
				s5.SetActive (false);
				topText.text = "Mission: Survive for 2 Minutes\n \t\t OR\n Mission: Defeat All Enemies";
				bottomText.text = " ";
				break;
			case 3:
				s8.SetActive (false);
				s4.SetActive (true);
				bottomText.text = "Akane: Two minutes is more than enough time to wipe the floor with these invaders";
				break;
			case 2:
				s9.SetActive (false);
				s5.SetActive (true);
				topText.text = "Lonk: If we can hold on for about two minutes, we can use the satellite interference" +
				" to break them up into groups";
				break;
			case 1:
				s8.SetActive (true);
				bottomText.text = "Vinny: Guys get ready, there are a lot of them";
				break;
			case 0:
				s9.SetActive (true);
				topText.text = "C. Orange: Foolish humans, you really think you can beat the orange division?" +
				" Orange Crew, time for an all out attack!";
				bottomText.text = " ";
				break;
			}
		} else {
			switch (count) {
			// Fourth row
			case 8:
				Exit (2);
				break;
			case 7:
				s8.SetActive (false);
				s6.SetActive (true);
				bottomText.text = "Lonk: Guys look, the aliens are still here";
				break;
			case 6:
				topText.text = "Akane: Satellite still up and running over here";
				break;
			case 5:
				s8.SetActive (true);
				s6.SetActive (false);
				bottomText.text = "Vinny: Akane, is your satellite still functioning?";
				break;
			case 4:
				s7.SetActive (false);
				s3.SetActive (true);
				topText.text = "Akane: Lonk, what do you mean you weren't expecting there to be that many. " +
				"We are going up against an entire race of aliens. For all we know there could be 100 million";
				break;
			case 3:
				s4.SetActive (false);
				s6.SetActive (true);
				bottomText.text = "Lonk: Everything is A-OK here." +
				" Though I really wasn't expecting that many aliens";
				break;
			case 2:
				topText.text = "Vinny: I know, I was talking about if everyones satellites were still operational";
				break;
			case 1:
				s4.SetActive (true);
				bottomText.text = "Akane: Boss, you do remember that we are controlling the satellites from home base right?";
				break;
			case 0:
				s7.SetActive (true);
				topText.text = "Vinny: Is everyone okay?";
				bottomText.text = " ";
				break;
			}
		}
	}

	void DialogueThree (int type, int count)
	{

		if (type == 0) {
			switch (count) {
			// Fourth row
			case 7:
				Exit (4);
				break;

			// Fifth row / front row
			case 6:
				s8.SetActive (false);
				s5.SetActive (false);
				topText.text = "Mission: Defeat All Enemies in 3 Minutes";
				bottomText.text = " ";
				break;
			case 5:
				s8.SetActive (true);
				s10.SetActive (false);
				bottomText.text = "Vinny: Well, what're we waiting for then? Let's go!";
				break;
			case 4:
				topText.text = "Lonk: Guys, these 2 rows are only stunned for three minutes, we need to act fast.";
				break;
			case 3:
				s4.SetActive (false);
				s10.SetActive (true);
				bottomText.text = "C. Orange: This is a funny trick you've pulled, but irregardless you will still lose.";
				break;
			case 2:
				s7.SetActive (false);
				s5.SetActive (true);
				topText.text = "Lonk: Yes, though it looks like some of them were able to get away";
				break;
			case 1:
				s4.SetActive (true);
				bottomText.text = "Akane: Is this from the satellite frequency?";
				break;
			case 0:
				s7.SetActive (true);
				topText.text = "Vinny: It looks like 2 rows of invaders are stunned";
				bottomText.text = " ";
				break;
			}
		} else {
			switch (count) {
			// Fourth row
			case 5:
				Exit (2);
				break;
			case 4:
				s3.SetActive (false);
				s5.SetActive (true);
				topText.text = "Lonk: Boo, you guys are no fun";
				break;
			case 3:
				s8.SetActive (true);
				s6.SetActive (false);
				bottomText.text = "Vinny: I agree with Akane, the next wave could be here any second";
				break;
			case 2:
				s9.SetActive (false);
				s3.SetActive (true);
				topText.text = "Akane: Lonk, I think it's just a little early to get excited, I mean the big bad boss is just chilling outside.";
				break;
			case 1:
				s6.SetActive (true);
				bottomText.text = "Lonk: Take that you alien scum.";
				break;
			case 0:
				s9.SetActive (true);
				topText.text = "C. Orange: Curses, you've wiped out half of my men.";
				bottomText.text = " ";
				break;
			}
		}
	}

	void DialogueFour (int type, int count)
	{
		if (type == 0) {
			switch (count) {
			// Fourth row
			case 5:
				Exit (4);
				break;

			// Fifth row / front row
			case 4:
				s7.SetActive (false);
				s4.SetActive (false);
				topText.text = "Mission: Defeat All Enemies";
				bottomText.text = " ";
				break;
			case 3:
				s6.SetActive (false);
				s4.SetActive (true);
				bottomText.text = "Akane: That's easier said than done";
				break;
			case 2:
				s7.SetActive (true);
				s9.SetActive (false);
				topText.text = "Vinny: It's simple, we take them down one by one";
				break;
			case 1:
				s6.SetActive (true);
				bottomText.text = "Lonk: Boss, what're we going to do? It looks like they're getting into formation.";
				break;
			case 0:
				s9.SetActive (true);
				topText.text = "C. Orange: Remaining soldiers, it is time for checker formation. " +
				"It is also time for me to enjoy some falcon branded punch while you wipe out these humans";
				bottomText.text = " ";
				break;
			}
		} else {
			switch (count) {
			// Fourth row
			case 6:
				Exit (2);
				break;
			case 5:
				s8.SetActive (true);
				s4.SetActive (false);
				bottomText.text = "Vinny: No, we must defeat him, otherwise earth will continue to be in danger";
				break;
			case 4:
				s9.SetActive (false);
				s5.SetActive (true);
				topText.text = "Lonk: We should just leave him be, we can skip him and move on.";
				break;
			case 3:
				s8.SetActive (false);
				s4.SetActive (true);
				bottomText.text = "Akane: Boss, I don't think he heard you.";
				break;
			case 2:
				topText.text = "C. Orange: Hic. Maybe if I drink more punch, I'll be able to see them again.";
				break;
			case 1:
				s8.SetActive (true);
				bottomText.text = "Vinny: You can't see any of them because they are gone.";
				break;
			case 0:
				s9.SetActive (true);
				topText.text = "C. Orange: Hic. I think I may have had too much punch. I can't see any of my men.";
				bottomText.text = " ";
				break;
			}
		}
	}

	void DialogueFive (int type, int count)
	{
		if (type == 0) {
			switch (count) {
			// Fourth row
			case 9:
				Exit (4);
				break;

			// Fifth row / front row
			case 8:
				s8.SetActive (false);
				s3.SetActive (false);
				topText.text = "Mission: Defeat Commander Orange";
				bottomText.text = " ";
				break;
			case 7:
				s8.SetActive (true);
				s10.SetActive (false);
				bottomText.text = "Vinny: We must win for the safety of earth";
				break;
			case 6:
				s5.SetActive (false);
				s3.SetActive (true);
				topText.text = "Akane: Here he comes guys";
				break;
			case 5:
				s8.SetActive (false);
				s10.SetActive (true);
				bottomText.text = "C. Orange, You filthy humans think you can best me. " +
				"I'm gonna make it rain, you got no chance to beat me";
				break;
			case 4:
				topText.text = "Lonk: Boss!? Why are you challenging him, we could've just skipped by him";
				break;
			case 3:
				s8.SetActive (true);
				s4.SetActive (false);
				bottomText.text = "Vinny: Commander Orange, step aside or prepare to be beaten like the rest of your crew";
				break;
			case 2:
				s9.SetActive (false);
				s5.SetActive (true);
				topText.text = "Lonk: No idea";
				break;
			case 1:
				s4.SetActive (true);
				bottomText.text = "Akane: Anyone know who he's talking about?";
				break;
			case 0:
				s9.SetActive (true);
				topText.text = "C. Orange: Yooooooo! Siggyyyyy! Phidoooooooo! Wassssssup";
				bottomText.text = " ";
				break;
			}
		} else {
			switch (count) {
			// Fourth row
			case 9:
				Exit (2);
				break;
			case 8:
				s7.SetActive (false);
				s4.SetActive (false);
				topText.text = "Congratulations!\nYou've beaten the demo!";
				bottomText.text = "";
				break;
			case 7:
				s7.SetActive (true);
				s5.SetActive (false);
				topText.text = "Vinny: This is no time to celebrate. The war for the safety of humanity has just begun";
				break;
			case 6:
				bottomText.text = "Akane: Well, we can celebrate our victory here";
				break;
			case 5:
				s5.SetActive (true);
				topText.text = "Lonk: Talk about having a killer stomach ache";
				break;
			case 4:
				s8.SetActive (false);
				s4.SetActive (true);
				bottomText.text = "Akane: Eww, his guts exploded everywhere";
				break;
			case 3:
				s9.SetActive (false);
				topText.text = "BOOOOOOOOM";
				break;
			case 2:
				topText.text = "C. Orange: Woah, I'm glowing. Hrrk. Cool.";
				break;
			case 1:
				s8.SetActive (true);
				bottomText.text = "Vinny: Everyone, move the satellites ahead NOW";
				break;
			case 0:
				s9.SetActive (true);
				topText.text = "C. Orange: Hrk, I don't feel so good";
				bottomText.text = " ";
				break;
			}
		}
	}
}
