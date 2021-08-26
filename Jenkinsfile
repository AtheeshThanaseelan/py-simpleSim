pipeline {
    agent { dockerfile true }

    stages {
        stage('Build') {
            steps {
                echo 'Building..'
                sh 'ls'
                sh 'ls /usr/include'
                sh 'python3 -m build --wheel --outdir build/ c_module_source/sim/'	
                stash(name: 'compiled-results', includes: 'build/*.pyc*')	
            }
        }
        stage('Test') {
            steps {
                echo 'Testing..'
                sh 'pip install build/physicsEnv*.whl'
                sh 'pip install pytest'
                sh 'pytest --junit-xml test-reports/results.xml test_sample.py'
		
            }
            post {
                always {
                    junit 'test-reports/results.xml'
                }
            }
        }
        stage('Deploy') {
            steps {
                echo 'Deploying....'
            }
        }
    }
}