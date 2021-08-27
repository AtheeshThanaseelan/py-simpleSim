pipeline {
    agent none

    stages {
        stage('Build') {
            agent{dockerfile true}
            steps {
                echo 'Building..'
                sh 'python3 -m build --wheel --outdir build/ c_module_source/sim/'	
                //sh 'ls build/'
                stash(name: 'compiled-results', includes: 'build/*.whl')	
            }
        }
        stage('Test') {
            agent{
                dockerfile{
                    dir 'build_scripts'
                }
            }
            
            steps {
                unstash 'compiled-results'
                sh 'ls /home/jenkins'
                sh """
                    . /home/jenkins/venv/bin/activate
                    pip install build/physicsEnv*.whl
                    """
                /*
                withEnv(["HOME=${env.WORKSPACE}"]) {
                    unstash 'compiled-results'
                    sh 'ls'
                    echo 'Testing..'
                    sh 'pip debug --verbose'
                    sh 'python3 -m pip install build/physicsEnv*.whl'
                    sh 'pytest --junit-xml test-reports/results.xml test_sample.py'
                }
                */
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