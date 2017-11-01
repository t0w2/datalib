node {
    properties(
        [
            pipelineTriggers([cron('H/5 * * * *')]),
        ]
    )

    stage('Status Checking') {
        if (env.CHANGE_ID) {
            SHA = sh(
                script: "curl https://eos2git.cec.lab.emc.com/api/v3/repos/wangw5/datalib/pulls/${CHANGE_ID} 2> /dev/null | python -c \"import sys, json; print json.load(sys.stdin)['head']['sha']\"",
                returnStdout: true
            ).trim()
            STATUS = sh(
                script: "curl https://eos2git.cec.lab.emc.com/api/v3/repos/wangw5/datalib/commits/${SHA}/status 2> /dev/null | python -c \"import sys, json; print json.load(sys.stdin)['state']\"",
                returnStdout: true
            ).trim()
            //STATUS = sh(
            //    script: "curl https://eos2git.cec.lab.emc.com/api/v3/repos/wangw5/datalib/commits/${SHA}/status 2> /dev/null | python -c \"import sys, json; checks = json.load(sys.stdin); num = len(checks['statuses']); print 'No checks found.' if (num <= 1) else ''; print ', '.join([checks['statuses'][i]['context'] + ' is ' + checks['statuses'][i]['state'] for i in range(num) if not (checks['statuses'][i]['state'] == 'success' or checks['statuses'][i]['context'] == 'continuous-integration/jenkins/pr-merge')])\"",
            //    returnStdout: true
            //).trim()
            if (STATUS != "success") {
                currentBuild.result = 'NOT_BUILT'
                error("Status Checking returns: ${STATUS}. Do not build until Status Checking returns 'success'")
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
                    script: "curl -X PUT -d '{\"commit_title\": \"Merge pull request\"}'  https://${credentials}@eos2git.cec.lab.emc.com/api/v3/repos/wangw5/datalib/pulls/${CHANGE_ID}/merge 2> /dev/null | python -c \"import sys, json; print json.load(sys.stdin)['message']\"",
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
                script: "curl https://eos2git.cec.lab.emc.com/api/v3/repos/wangw5/datalib/pulls/${CHANGE_ID} 2> /dev/null | python -c \"import sys, json; print json.load(sys.stdin)['head']['ref']\"",
                returnStdout: true
            ).trim()
            TARGET_BRANCH = sh(
                script: "curl https://eos2git.cec.lab.emc.com/api/v3/repos/wangw5/datalib/pulls/${CHANGE_ID} 2> /dev/null | python -c \"import sys, json; print json.load(sys.stdin)['base']['ref']\"",
                returnStdout: true
            ).trim()
            echo "Pull Request ${CHANGE_ID} merged ${SOURCE_BRANCH} to ${TARGET_BRANCH}."
            echo "Go to rebase from ${TARGET_BRANCH} back to ${SOURCE_BRANCH}."
            build job: 'git_branch_merge_pipeline', parameters: [string(name: 'SOURCE_BRANCH', value: "${TARGET_BRANCH}"), string(name: 'TARGET_BRANCH', value: "${SOURCE_BRANCH}")], wait: false
        }
    }
}
