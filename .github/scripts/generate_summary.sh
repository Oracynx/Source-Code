#!/usr/bin/env bash
set -euo pipefail

# 计算前一天日期（UTC+8 时区）
YESTERDAY=$(TZ=Asia/Shanghai date -d 'yesterday' '+%Y-%m-%d')
LOG_FILE="${YESTERDAY}.md"

# 获取当天 00:00–23:59:59 的提交记录
GIT_LOG=$(git log \
  --since="${YESTERDAY} 00:00:00" \
  --until="${YESTERDAY} 23:59:59" \
  --pretty=format:"- %h %ad %an: %s" \
  --date=iso)

if [[ -z "${GIT_LOG}" ]]; then
  echo "[$YESTERDAY] 无提交，退出。"
  exit 0
fi

# 调用 OpenAI（DeepSeek）API
RESPONSE=$(python3 - <<'EOF'
import os, requests, json

url = os.environ['DEEPISEEK_API_URL']  # e.g. https://api.openai.com/v1/chat/completions
api_key = os.environ['DEEPISEEK_API_KEY']
prompt = os.environ['DEEPISEEK_PROMPT']
model  = os.environ.get('DEEPISEEK_MODEL', 'gpt-3.5-turbo')

# 构造 OpenAI Chat payload
payload = {
    "model": model,
    "messages": [
        {"role": "system", "content": prompt},
        {"role": "user", "content": """%s""" % os.environ.get('GIT_LOG_RAW')}
    ]
}

# 注意：将 GIT_LOG 通过环境变量传入
# 由于 bash 的变量展开是在 EOF 外部，这里我们改用环境变量
import subprocess
git_log = subprocess.check_output(
    ["bash", "-lc", "printf \"%s\" \"$GIT_LOG\""],
    universal_newlines=True
)
payload["messages"][1]["content"] = git_log

headers = {
    "Authorization": f"Bearer {api_key}",
    "Content-Type": "application/json",
}

resp = requests.post(url, headers=headers, json=payload)
resp.raise_for_status()
result = resp.json()['choices'][0]['message']['content']
print(result)
EOF
)

# 写入 Markdown
{
  echo "# 提交摘要 — ${YESTERDAY}"
  echo
  echo "${RESPONSE}"
} > "${LOG_FILE}"