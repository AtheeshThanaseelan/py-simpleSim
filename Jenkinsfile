pipeline {
    agent { dockerfile true }

    stages {
        stage('Build') {
            steps {
		sh 'ls'
		sh 'ls /usr/include'
                echo 'Building..'
            }
        }
        stage('Test') {
            steps {
                echo 'Testing..'
            }
        }
        stage('Deploy') {
            steps {
                echo 'Deploying....'
            }
        }
    }
}