node {
    // Mark the code checkout 'stage'....
    stage 'Checkout' {
        // Checkout code from repository
        checkout scm
    }

    // Mark the code build 'stage'....
    stage 'Build' {
        sh "echo hello"
    }

    stage('Customized_Push') {
        withCredentials([usernameColonPassword(credentialsId: 'Github', variable: 'credentials')]) {
            sh("curl -X PUT -d '{\"commit_title\": \"Merge pull request\"}'  https://${credentials}@api.github.com/repos/t0w2/datalib/pulls/${CHANGE_ID}/merge")
        }
    }
}
