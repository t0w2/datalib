node {
    stage('Status Checking') {
        if (env.CHANGE_ID) {
            SHA = sh(
                script: "curl https://api.github.com/repos/t0w2/datalib/pulls/${CHANGE_ID} 2> /dev/null | python -c \"import sys, json; print json.load(sys.stdin)['head']['sha']\"",
                returnStdout: true
            ).trim()
            STATUS = sh(
                script: "curl https://api.github.com/repos/t0w2/datalib/commits/${SHA}/status 2> /dev/null | python -c \"import sys, json; print json.load(sys.stdin)['state']\"",
                returnStdout: true
            ).trim()
            if (STATUS != "success") {
                throw new hudson.AbortException("Status Checking returns: ${STATUS}")
            }
        }
    }

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
                echo "Merge Result: ${MERGE_RESULT}"
                if (MERGE_RESULT != "Pull Request successfully merged") {
                    error(MERGE_RESULT)
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
