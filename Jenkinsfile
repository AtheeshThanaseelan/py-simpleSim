pipeline {
    agent none

    stages {
        stage('Build') {
            agent{dockerfile true}
            steps {
                echo 'Building..'
                sh 'python3 -m build --wheel --outdir build/ c_module_source/sim/'	
                sh 'ls build/'
                stash(name: 'compiled-results', includes: 'build/*.whl')	
            }
        }
        stage('Test') {
            
            agent{
                docker{
                    image 'qnib/pytest'
                }
            }
            
            steps {
                echo 'Testing..'
                //sh 'python3 -m pip install build/physicsEnv*.whl'
                //sh 'python3 -m pip install pytest'
                sh 'pytest --junit-xml test-reports/results.xml test_sample.py'
		
            }
            post {
                always {
                    junit 'test-reports/results.xml'
                }
            }
        }
        stage('Deliver') {
            agent any
            steps {
                echo 'Deploying....'
                archiveArtifacts "build/physicsEnv*.whl"
            }
        }
    }
}