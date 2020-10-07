import firebase from 'firebase';
import 'firebase/database'

var config = {
    apiKey: "AIzaSyBrz1mgreuGwS8n_SGOnJmIyeGrtgVEvUQ",
    authDomain: "locust-project.firebaseapp.com",
    databaseURL: "https://locust-project.firebaseio.com",
    projectId: "locust-project",
    storageBucket: "locust-project.appspot.com",
    messagingSenderId: "966372321003",
    appId: "1:966372321003:web:cdba71a8f1598067c280ae",
    measurementId: "G-24R5YNW1KY"
  };


var fire = firebase.initializeApp(config);

export default fire;