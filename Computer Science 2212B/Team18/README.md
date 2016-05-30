# Welcome to Team 18's FitByte App

Our desktop app utilizes measuremnts that the fitbit can record to help the user understand how active they currently are.
The user could then use our app to set goals and motivate themselves to attain a more healthy and active lifestyle.

The desktop app was developed in Java using Swing UI Components. The app uses the FitBit API to pull various information 
(ex: floors climbed, steps taken, etc...) for displaying and calculation purposes. To connect to the FitBit API, OAuth2
Authentication's protocol was followed to pull data from a particular authenticated FitBit user. The libraries we have used are:
scribejava-apis, scribejava-core, and json. These libraries were used for JSON object parsing.

Link to the Fitbit API.
https://dev.fitbit.com/ca

Our UI was developed and is optimized to run on Mac OS. It will run on Windows; however, the UI will not look the same 
and could produce UNPREDICTABLE behaviour.

## Build 

To build our desktop app, clone our team's Bitbucket repository onto your local system:

```
git clone ssh://git@repo.gaul.csd.uwo.ca:7999/cs2212_w2016/team18.git
```

Then: 

```
mvn package
```

If you want to run the jar in test mode put in:

```
java -jar target/team18-1.0-SNAPSHOT-jar-with-dependencies.jar test
```

If you don't want to run in test mode

```
java -jar target/team18-1.0-SNAPSHOT-jar-with-dependencies.jar
```

The dependencies our app requires are the libraries listed above. The programs that are required
to build our desktop app are git, and maven.
 

## Documentation

Please checkout our doc folder which contains JavaDocs of all the classes we have created.