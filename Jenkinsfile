node {
    // Mark the code checkout 'stage'....
    stage('Checkout') {
        // Checkout code from repository
        checkout scm
    }

    // Mark the code build 'stage'....
    stage('Build') {
        sh("echo hello")
    }

    stage('Customized_Pull_Request_Merge') {
        if (env.CHANGE_ID) {
            withCredentials([usernameColonPassword(credentialsId: 'Github', variable: 'credentials')]) {
                sh("curl -X PUT -d '{\"commit_title\": \"Merge pull request\"}'  https://${credentials}@api.github.com/repos/t0w2/datalib/pulls/${CHANGE_ID}/merge")
            }
        }
    }
    
    stage('Rebase') {
        if (env.CHANGE_ID) {
            TARGET_BRANCH = sh(
                script: "curl https://api.github.com/repos/t0w2/datalib/pulls/${CHANGE_ID} 2> /dev/null | python -c \"import sys, json; print json.load(sys.stdin)['base']['ref']\"",
                returnStdout: true
            ).trim()
            echo "SOURCE_BRANCH: ${TARGET_BRANCH}"
            echo "TARGET_BRANCH: ${BRANCH_NAME}"
            
            build job: 'git_branch_merge_pipeline', parameters: [string(name: 'SOURCE_BRANCH', value: "${TARGET_BRANCH}"), string(name: 'TARGET_BRANCH', value: "${BRANCH_NAME}")], wait: false
        }
    }
}
