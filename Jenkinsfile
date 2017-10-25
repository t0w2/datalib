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
                MERGE_RESULT = sh(
                    script: "curl -X PUT -d '{\"commit_title\": \"Merge pull request\"}'  https://${credentials}@api.github.com/repos/t0w2/datalib/pulls/${CHANGE_ID}/merge 2> /dev/null | python -c \"import sys, json; print json.load(sys.stdin)['message']\"",
                    returnStdout: true
                ).trim()
                
                if (MERGE_RESULT == "At least one approved review is required by reviewers with write access.") {
                    currentBuild.result = 'FAILURE'
                }
            }
        }
    }
    
    stage('Rebase') {
        if (env.CHANGE_ID) {
            SOURCE_BRANCH = sh(
                script: "curl https://api.github.com/repos/t0w2/datalib/pulls/${CHANGE_ID} 2> /dev/null | python -c \"import sys, json; print json.load(sys.stdin)['head']['ref']\"",
                returnStdout: true
            ).trim()
            TARGET_BRANCH = sh(
                script: "curl https://api.github.com/repos/t0w2/datalib/pulls/${CHANGE_ID} 2> /dev/null | python -c \"import sys, json; print json.load(sys.stdin)['base']['ref']\"",
                returnStdout: true
            ).trim()
            echo "Pull Request ${CHANGE_ID} merged ${SOURCE_BRANCH} to ${TARGET_BRANCH}."
            echo "Go to rebase from ${TARGET_BRANCH} back to ${SOURCE_BRANCH}."
            build job: 'git_branch_merge_pipeline', parameters: [string(name: 'SOURCE_BRANCH', value: "${TARGET_BRANCH}"), string(name: 'TARGET_BRANCH', value: "${SOURCE_BRANCH}")], wait: false
        }
    }
}
